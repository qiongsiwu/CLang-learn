/* Exercise 5-2 */
#include <ctype.h>
#include <stdio.h>
#include <math.h>

int getch(void);
void ungetch(int); 

int getfloat(float *); 

int main()
{
    printf("Hello world!\n"); 
    int i; 
    float n = 0.0; 
    i = 1; 
    float *pn = &n;  
    
    while (i != EOF) {
	i = getfloat(pn); 
	if (i > 0)
	    printf("%f\n", n); 
    }
}

/* getfloat: get next float from input to *pn 
   based on atof in Exercise 4-2
 */
/* returns
   - EOF for end of file
   - zero if input is not a number
   - 1 if the input is a number
 */
int getfloat(float *pn)
{
    int c; 
    float sign, power, expsign, exp; 
    while (isspace(c = getch())) /* skip white space */
	; 
    
    sign = (c == '-')? -1.0 : 1.0;   /* sign */
    if (c == '+' || c == '-') {  
	c = getch(); 
	if (!isdigit(c)) {
	    ungetch(c); 
	    return 0; 
	}
    }

    for (*pn = 0.0; isdigit(c); c = getch()) /* integer part */
	*pn = 10.0 * *pn + (c - '0');

    if (c == '.') {
	c = getch(); 
	if (!isdigit(c)) {
	    ungetch(c); 
	    return 1; 
	}
    }

    for (power = 1.0; isdigit(c); c = getch()) { /* fraction part */ 
	*pn = 10 * *pn + (c - '0'); 
	power *= 10.0; 
    }

    *pn = sign * (*pn / power);

    if (c == 'e' || c == 'E') {
	c = getch(); 
	if (!isdigit(c) && c != '+' && c != '-') {
	    ungetch(c); 
	    return 1; 
	}
    }

    expsign = (c == '-')? -1 : 1; 
    if (c == '+' || c == '-') {  
	c = getch(); 
	if (!isdigit(c)) {
	    ungetch(c); 
	    return 1; 
	}
    }

    for (exp = 0.0; isdigit(c); c = getch())
	exp += 10 * exp + (c - '0'); 

    exp = pow(10.0, expsign * exp); 

    *pn = *pn * exp; 
    
    if (c != EOF) {
	ungetch(c);
	return 1; 
    } else
	return EOF; 
}

/* getch and ungetch */
#define BUFSIZE 100  
int buf[BUFSIZE];  /* buffer for ungetch  - Exercise 4-9 */
int bufp = 0;      /* next free position in buf */

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar(); 
}

void ungetch(int c) /* push character back on input */
{
    if (bufp >= BUFSIZE)
	printf("ungetch: too many characters\n"); 
    else
	buf[bufp++] = c; 
}
