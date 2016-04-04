/* Exercise 5-1 */
#include <ctype.h>
#include <stdio.h>

int getch(void);
void ungetch(int); 

int getint(int *); 

int main()
{
    printf("Hello world!\n"); 
    int n, i; 
    n = 0; 
    i = 1; 
    int *pn = &n;  
    
    while (i != EOF) {
	i = getint(pn); 
	if (i > 0)
	    printf("%d\n", n); 
    }
}

/* getint: get next integer from input into *pn */
/* returns
   - EOF for end of file
   - 0 if the next input is not a number
   - positive value if the input contains a valid number. 
*/
int getint(int *pn)
{
    int c, sign; 
    while (isspace(c = getch())) /* skip white space */
	; 
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
	ungetch(c);  /* it's not a number */ 
	return 0; 
    }
    sign = (c == '-')? -1 : 1; 
    if (c == '+' || c == '-') {
	c = getch(); 
	if (!isdigit(c)) {
	    ungetch(c); 
	    return 0; 
	}
    }
    for (*pn = 0; isdigit(c); c = getch())
	*pn = 10 * *pn + (c - '0'); 
    *pn *= sign; 
    if (c != EOF)
	ungetch(c); 
    return c; 
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
