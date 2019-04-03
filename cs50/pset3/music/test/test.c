#include <stdio.h>
#include <cs50.h>

int duration(string fraction)
{
    char cnum1 = fraction[0];
    char cnum2 = fraction[2];

    printf("%c", cnum2);

    int inum1 = atoi(&cnum1);
    int inum2 = atoi(&cnum2);
    int inum3 = cnum2 - 0;

    printf("num1: %d\n", inum1);
    printf("num2: %d\n", inum2);
    printf("num3: %d\n", inum3);

    int r = (inum1/inum2)/0.125;

    //printf("%d", r);
    //int r = (frac[0]/frac[2])/0.125;
    // Divide fraction[0] by fraction[2]
    // Divide result of line above by 0.125
    // return result of line above

    // TODO

    return 0;
}

int main()
{
	char test[3] = "1/4";
	int x = duration("1/4");
	//printf(atoi(duration(test)));
	return 0;
}