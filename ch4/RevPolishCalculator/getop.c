#include <stdio.h>
#include <ctype.h>
#include "calc.h"
#define BUFSIZE 100

/* Exercise 4-10 */
int getop(char s[])
{
    static char buf[BUFSIZE]; 
    static int bufp = 0; 
    int i, c; 

    c = (bufp > 0)? buf[--bufp] : getchar(); 
	
    while ((s[0] = c) == ' ' || c == '\t') {
	c = (bufp > 0)? buf[--bufp] : getchar();
    } 

    s[1] = '\0'; 
    if (!isdigit(c) && c != '.')
	return c; /* not a number */
    i = 0; 
    if (isdigit(c)) /* collect integer part */
	while (isdigit(s[++i] = c = getch()))
	    ;
    if (c == '.')
	while (isdigit(s[++i] = c = getch()))
	    ; 
    s[i] = '\0'; 
    if (c != EOF) {
        if (bufp >= BUFSIZE)
	    printf("static buffer is full"); 
	else 
	    buf[bufp++] = c; 
    } 
    return NUMBER; 
}
