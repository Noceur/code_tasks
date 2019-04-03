import sys

lower_low = ord('a')
lower_high = ord('z')
upper_low = ord('A')
upper_high = ord('Z')


def main():
    if(len(sys.argv) != 2):
        print("Usage: python ceasay.py k")
        exit(1)

    else:
        string = input("plaintext: ")
        print("ciphertext: ", end="")
        for c in string:
            c2 = ord(c)
            if(c2 >= lower_low and c2 <= lower_high):
                print(chr((((c2 + int(sys.argv[1])) - lower_low) % 26) + lower_low), end="")
            elif(c2 >= upper_low and c2 <= upper_high):
                print(chr((((c2 + int(sys.argv[1])) - upper_low) % 26) + upper_low), end="")

            else:
                print(c, end="")

    print()
    return 0


main()
