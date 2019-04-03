quarter = 25
dime = 10
nickel = 5
penny = 1


def get_input():
    while True:
        x = input("Change owed: ")
        try:
            x = float(x)
            if(x < 0):
                continue
                print("test")
            return x
        except (ValueError, TypeError):
            pass


def get_coins(cents, coin_count, coin_type):
    while cents >= coin_type:
        cents -= coin_type
        coin_count += 1
        print(cents)
    return (cents, coin_count)


def main():
    coin_count = 0
    x = get_input()
    x = int(x * 100)
    (x, coin_count) = get_coins(x, coin_count, quarter)
    (x, coin_count) = get_coins(x, coin_count, dime)
    (x, coin_count) = get_coins(x, coin_count, nickel)
    (x, coin_count) = get_coins(x, coin_count, penny)
    print(coin_count, "coins.")


main()