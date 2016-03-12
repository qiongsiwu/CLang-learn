/* Exercise 4-2 */

/* Extend atof to handle scientific notation of the form 
   123.45e-6
   where a floating point number may be followed by e or E 
   and an optionally signed exponent. 
*/

/* compile with clang Atof.c -Wall -lm to link the math library */

#include <stdio.h>
#include <ctype.h>
#include <math.h>

#define MAX_STR_LEN 1024

double atof(char s[]); 

int main() 
{
    char s1[MAX_STR_LEN] = "1.23456"; 
    printf("%f\n", atof(s1)); 

    char s2[MAX_STR_LEN] = "-12.23456"; 
    printf("%f\n", atof(s2)); 

    char s3[MAX_STR_LEN] = "0"; 
    printf("%f\n", atof(s3)); 

    char s4[MAX_STR_LEN] = "1.23456E3"; 
    printf("%f\n", atof(s4)); 

    char s5[MAX_STR_LEN] = "1.23456e-3"; 
    printf("%.8f\n", atof(s5)); 
}

/* atof: convert string s to double */
double atof(char s[])
{
    double val, power, exp; // exp is for the optional signed exponent
    int i, sign, expsign; // expsign is the sign for the optional exponent

    for (i = 0; isspace(s[i]); i++) /* skip spaces */
	; 

    sign = (s[i] == '-')? -1 : 1;   

    if (s[i] == '+' || s[i] == '-')
	i++; 
    for (val = 0.0; isdigit(s[i]); i++)
	val = 10.0 * val + (s[i] - '0'); 
    if (s[i] == '.')
	i++; 
    for (power = 1.0; isdigit(s[i]); i++) {
	val = 10.0 * val + (s[i] - '0'); 
	power *= 10.0; 
    }
    
    if (s[i] == 'E' || s[i] == 'e')
	i++; 
    expsign = (s[i] == '-')? -1 : 1; 
    if (s[i] == '+' || s[i] == '-')
	i++; 
    for (exp = 0.0; isdigit(s[i]); i++) {
	exp += 10 * exp + (s[i] - '0'); 
    }

    exp = pow(10.0, expsign * exp);     

    return sign * (val / power) * exp; 
}


