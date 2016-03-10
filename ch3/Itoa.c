/* Exercise 3-4 */
/* Exercise 3-5 */

#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAX_STR_LEN 1024

void itoa(int n, char s[]); 
void itoa2(int n, char s[]); 
void itoa3(int n, char s[], int w); 
void itob(int n, char s[], int b); 

int itoc(int n); 
void reverse(char s[]); 

int main()
{
    printf("Hello world\n"); 
    char s[MAX_STR_LEN];
    int i, b; 

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

    i = 16; 
    b = 2;    
    itob(i, s, b); 
    printf("%d\t%s\n", i, s);

    i = 16; 
    b = 4;    
    itob(i, s, b); 
    printf("%d\t%s\n", i, s);

    i = 16; 
    b = 8;    
    itob(i, s, b); 
    printf("%d\t%s\n", i, s);

    i = 16; 
    b = 16;    
    itob(i, s, b); 
    printf("%d\t%s\n", i, s);

    i = -15; 
    b = 16;    
    itob(i, s, b); 
    printf("%d\t%s\n", i, s);

    i = INT_MAX; 
    b = 16;    
    itob(i, s, b); 
    printf("%d\t%s\t%x\n", i, s, i);

    i = 256;
    itoa3(i, s, 5); 
    printf("%d\t%s\n", i, s); 
    
    i = INT_MIN; 
    itoa3(i, s, 5); 
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

/* Exercise 3-4 */
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

/* Exercise 3-5 */
/* itob: convert n into a base b character representation
   in the string s. 
   Accepted value for b: 1 < b <= 36. 
   If b > 36, we run out of digits and letters. 
*/
void itob(int n, char s[], int b)
{
    int i, sign; 
    if ((sign = n) > 0)
	n = -n;
    i = 0; 
    do {
	s[i++] = itoc(-(n % b)); 
    } while ((n /= b) < 0); 
    if (sign < 0)
	s[i++] = '-'; 
    s[i] = '\0'; 
    reverse(s); 
}

/* itoc: convert n into a character 
   Note that if n > 36, the result is not valid. 
 */
int itoc(int n)
{
    if (n < 10)
	return '0' + n; 
    else 
	return n - 10 + 'a'; 
}

/* Exercise 3-6 */
/* itoa3: convert n into characters in s. s has a min width of 
   w. If the number of digits is less than w, blanks are padded. 
   w > 0 is required. 
*/
void itoa3(int n, char s[], int w)
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
    
    while (i < w)
	s[i++] = ' '; 

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
