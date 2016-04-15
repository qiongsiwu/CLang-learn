/* Exercise 1-20 */
#include <stdio.h>
#include "Tab.h"

extern int tabstop; /* size of a tab */ 

int main()
{
    int c; 
    while ((c = getchar()) != EOF) {
	if (c == '\t') 
	    for (int i = 0; i < tabstop; i++)
		putchar(' '); 
	else 
	    putchar(c); 
    }
    return 0; 
}
