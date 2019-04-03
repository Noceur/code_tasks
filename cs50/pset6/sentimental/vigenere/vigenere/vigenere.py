import sys

lower_low = ord('a')
lower_high = ord('z')
upper_low = ord('A')
upper_high = ord('Z')


def validate_argv():
    if(len(sys.argv) != 2 or not sys.argv[1].isalpha() or (' ' in sys.argv[1]) == True):
        print("Usage: python vigenere.py k")
        return False
    else:
        return True


def main():
    output = ""
    if(not validate_argv()):
        exit(1)
    else:
        counter = 0
        string = input("plaintext: ")
        print("ciphertext: ", end="")
        for c in string:
            if (sys.argv[1][counter % len(sys.argv[1])].islower()):
                current = ord(sys.argv[1][counter % len(sys.argv[1])]) - lower_low
            else:
                current = ord(sys.argv[1][counter % len(sys.argv[1])]) - upper_low

            c2 = ord(c)
            if(c2 >= lower_low and c2 <= lower_high):
                print(chr((((c2 + current) - lower_low) % 26) + lower_low), end="")
                counter += 1
            elif(c2 >= upper_low and c2 <= upper_high):
                print(chr((((c2 + current) - upper_low) % 26) + upper_low), end="")
                counter += 1
            else:
                print(c, end="")

    print()
    return 0


main()
