/* Exercise 3-4 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_STR_LEN 1024

void itoa(int n, char s[]); 
void itoa2(int n, char s[]); 
void reverse(char s[]); 

int main()
{
    printf("Hello world\n"); 
    char s[MAX_STR_LEN];
    int i; 

    i = 256;
    itoa(i, s); 
    printf("%d\t%s\n", i, s); 
    
    i = INT_MIN; 
    itoa(i, s); 
    printf("%d\t%s\n", i, s); /* does not print correctly */

    i = 256;
    itoa2(i, s); 
    printf("%d\t%s\n", i, s); 
    
    i = INT_MIN; 
    itoa2(i, s); 
    printf("%d\t%s\n", i, s); 

    i = INT_MAX; 
    itoa2(i, s); 
    printf("%d\t%s\n", i, s); 
}

/* itoa: convert n to characters in s */
/* This version does not work when n is INT_MIN, because the 
   int type cannot hold a positive value bigger than INT_MAX, 
   and INT_MAX = - INT_MIN - 1 < - INT_MIN
 */
void itoa(int n, char s[])
{
    int i, sign; 
    if ((sign = n) < 0) /* record sign */
	n = -n;         /* make n positive, failes for n = INT_MIN */
    i = 0; 
    do {                /* generate digits in reverse order */
	s[i++] = n % 10 + '0'; /* get next digit */
    } while (( n /= 10) > 0);   /* delete it */
    if (sign < 0)
	s[i++] = '-'; 
    s[i] = '\0';
    reverse(s); 
}

/* itoa2: convert n to characters in s. 
   This second deals with the largest negative number correctly. 
   % on a negative number works because C99 requires:
   a = (a / b) * b + a % b
 */
void itoa2(int n, char s[])
{
    int i, sign; 
    if ((sign = n) > 0)
	n = -n;         /* This does not overflow! */
    i = 0; 
    do {
	s[i++] = - (n % 10) + '0'; 
    } while ((n /= 10) < 0); 
    if (sign < 0)
	s[i++] = '-'; 
    s[i] = '\0'; 
    reverse(s); 
}


/* reverse: reversing string s in place */
void reverse(char s[])
{
    int c, i, j; 
    for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
	c = s[i]; 
	s[i] = s[j]; 
	s[j] = c; 
    }
}
