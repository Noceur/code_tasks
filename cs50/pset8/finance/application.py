import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
import json

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")
all_users = []
userlist = db.execute("SELECT username FROM users")
for user in userlist:
    all_users.append(user['username'])


@app.route("/")
@login_required
def index():
    updated_holdings = []
    holdings = db.execute("SELECT symbol, price, shares, date FROM shares WHERE id=\"" + session["user_id"] + "\"")
    cash = db.execute("SELECT cash FROM users WHERE id=\"" + session["user_id"] + "\"")[0]["cash"]
    total_portfolio = cash
    for row in holdings:
        row["purchase price"] = row.pop("price")
        current_price = lookup(row["symbol"])["price"]
        row["current price"] = current_price
        total_portfolio += current_price
        updated_holdings.append(row)
        total_portfolio = round(total_portfolio, 2)
    return render_template("index.html", list_py=updated_holdings, total_portfolio=total_portfolio, cash=cash)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        stock = lookup(symbol)
        user = db.execute("SELECT * FROM users WHERE id=\"" + session["user_id"] + "\"")[0]

        if stock is None:
            return apology("Stock symbol incorrect.")

        if shares.isdigit():
            shares = int(shares)
        else:
            return apology("shares not a positive integer.")

        if 0 > (user['cash'] - (stock['price'] * shares)):
            return apology("Not enough cash.")

        db.execute("UPDATE users SET cash=" + str(round(user['cash'] -
                                                        stock['price'] * shares, 2)) + " WHERE id=" + session["user_id"])
        db.execute("INSERT INTO shares (id, symbol, price, shares) VALUES(" +
                   session["user_id"] + ", \"" + symbol + "\", " + str(stock['price']) + ", " + str(shares) + ")")
        db.execute("INSERT INTO history (id, symbol, price, shares) VALUES(" +
                   session["user_id"] + ", \"" + symbol + "\", -" + str(stock['price']) + ", " + str(shares) + ")")

        cash = db.execute("SELECT cash FROM users WHERE id=\"" + session["user_id"] + "\"")[0]["cash"]

        return render_template("bought.html", title="Bought", symbol=symbol, shares=shares, stock=stock, total=shares * stock["price"], cash=cash)
    else:
        return render_template("buy.html")


@app.route("/check", methods=["GET"])
def check():
    global all_users
    if request.args.get('username') not in all_users and len(request.args.get('username')) > 0:
        return (jsonify(True))
    else:
        return (jsonify(False))


@app.route("/history")
@login_required
def history():
    holdings = db.execute("SELECT symbol, price, shares, date FROM history WHERE id=\"" + session["user_id"] + "\"")
    holdings.reverse()
    return render_template("history.html", list_py=holdings)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = str(rows[0]["id"])
        return index()

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    if request.method == "POST":
        # User reached route via POST (as by submitting a form via POST)
        try:
            symbol = request.form.get("symbol")
            stock = lookup(symbol)
            return render_template("quoted.html", name=stock['name'], price=stock['price'])
        except:
            return apology("Invalid symbol.", 400)

    else:
        return render_template("quote.html")


@app.route("/change_pass", methods=["GET", "POST"])
@login_required
def change_pass():

    if request.method == "POST":

        old_pass     = request.form.get("password")
        new_pass     = request.form.get("new_password")
        confirmation = request.form.get("confirm")

        if not new_pass:
            return apology("Missing password.", 400)

        if not (new_pass == confirmation):
            return apology("Password confirmation not same as password.", 400)

        new_pass = generate_password_hash(new_pass)

        rows = db.execute("SELECT * FROM users WHERE id = :user_id",
                          user_id=session["user_id"])

        # Ensure username exists and password is correct
        if not check_password_hash(rows[0]["hash"], old_pass):
            return apology("Invalid password", 403)

        db.execute("UPDATE users SET hash = :password",
                   password=new_pass)

        return index()

    else:
        return render_template("change_pass.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    global all_users
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Missing username.", 400)

        if request.form.get("username") in all_users:
            return apology("Duplicate username.", 400)

        if not request.form.get("password"):
            return apology("Missing password.", 400)

        if not (request.form.get("confirmation") == request.form.get("password")):
            return apology("Please repeat the password.", 400)

        if request.args.get('username') in all_users:
            return apology("User already exists.", 400)

        # Get user and 'make' password.
        username = request.form.get("username")
        password = generate_password_hash(request.form.get("password"))
        try:
            # Gets first row in reversed query then takes the list that is returned and gets the first element then the value in the key 'id' and pluses one.
            new_id = str(db.execute("SELECT id FROM users ORDER BY id DESC LIMIT 1")[0]['id'] + 1)
        except IndexError:
            new_id = "0"
        exe_string = "INSERT INTO users (id, username, hash, cash) VALUES (" + new_id + ", \"" + username + "\", \"" + password + "\", 10000);"
        db.execute(exe_string)

        # Remember which user has logged in.
        exe_string = "SELECT * FROM users WHERE username = \"" + username + "\""
        logged = db.execute(exe_string)
        session["user_id"] = new_id

        all_users.append(username)
        return render_template("index.html")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    holdings = db.execute("SELECT * FROM shares WHERE id=\"" + session["user_id"] + "\"")
    holdings_list = []
    for holding in holdings:
        holdings_list.append(holding["symbol"])

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        for asset in holdings:
            if asset["symbol"] == symbol:
                holding = asset
                continue

        if shares.isdigit():
            shares = int(shares)
        else:
            return apology("Not an int.", 400)

            flash("Not a integer!")
            return render_template("sell.html", holdings=holdings_list)

        if holding["shares"] - shares < 0:
            return apology("Not enough shares!", 400)

            flash("Not enough shares!")
            return render_template("sell.html", holdings=holdings_list)

        elif holding["shares"] - shares == 0:
            stock = lookup(symbol)
            user = db.execute("SELECT * FROM users WHERE id=\"" + session["user_id"] + "\"")[0]
            db.execute("UPDATE users SET cash=" + str(round(user['cash'] +
                                                            stock['price'] * shares, 2)) + " WHERE id=" + session["user_id"])
            db.execute("DELETE FROM shares WHERE id=" + session["user_id"] + " AND symbol =\"" + symbol + "\"")
            db.execute("INSERT INTO history (id, symbol, price, shares) VALUES(" +
                       session["user_id"] + ", \"" + symbol + "\", +" + str(stock['price']) + ", " + str(shares) + ")")

        else:
            stock = lookup(symbol)
            user = db.execute("SELECT * FROM users WHERE id=\"" + session["user_id"] + "\"")[0]
            db.execute("UPDATE users SET cash=" + str(round(user['cash'] +
                                                            stock['price'] * shares, 2)) + " WHERE id=" + session["user_id"])
            db.execute("UPDATE shares SET shares=" + str(holding["shares"] - shares) + " WHERE id=" + session["user_id"])
            db.execute("INSERT INTO history (id, symbol, price, shares) VALUES(" +
                       session["user_id"] + ", \"" + symbol + "\", +" + str(stock['price']) + ", " + str(shares) + ")")

        cash = db.execute("SELECT cash FROM users WHERE id=\"" + session["user_id"] + "\"")[0]["cash"]

        return render_template("bought.html", title="sold", symbol=symbol, shares=shares, stock=stock, total=shares * stock["price"], cash=cash)

        return render_template("sell.html", holdings=holdings_list)

    else:
        #print("GET METHOD")
        return render_template("sell.html", holdings=holdings_list)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
