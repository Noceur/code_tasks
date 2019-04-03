#include <stdio.h>
#include <string.h>
#include <cs50.h>
#include <math.h>

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
	float fnum1 = atof(&fraction[0]);
	float fnum2 = atof(&fraction[2]);

    return ((fnum1/fnum2)/0.125);
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
	char n = note[0];
	int n2 = 0;
	int o = atoi(&note[strlen(note)-1]);
	int o2 = o*12;

	if(n == 'C'){
		n2 = 1;
	}
	if(n == 'D'){
		n2 = 3;
	}
	if(n == 'E'){
		n2 = 5;
	}
	if(n == 'F'){
		n2 = 6;
	}
	if(n == 'G'){
		n2 = 8;
	}
	if(n == 'A'){
		n2 = 10;
	}
	if(n == 'B'){
		n2 = 12;
	}

	if(strlen(note) == 3){
		if(note[1] == '#'){
			n2++;
		}
		else{
			n2--;
		}
}

int r = (o2+n2)-9;
int k = -49+r;

float result = (pow(2.0f, (k/12.0f))*440.0f);
//printf("%f\n", result);
return round(result);

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if(s[0] == '\0')
    {
       return true;
    }
    return false;
}