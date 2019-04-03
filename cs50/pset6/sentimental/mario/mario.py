def validate_input(x):
    if(x < 0 or x > 23 or not isinstance(x, int)):
        return False
    else:
        return True


def pyramid(x):
    count = 0
    while count < x:
        print(" " * (x - 1 - count) + "#" * (count + 1) + "  " + "#" * (count + 1))
        count += 1


def main():
    exit = False
    while not exit:
        try:
            x = input("Height: ")
            x = int(x)
        except:
            continue
        if(validate_input(x)):
            pyramid(x)
            exit = True


main()