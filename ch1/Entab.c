/* Exercise 1-21 */
#include <stdio.h>
#include "Tab.h"

#define CHAR_SEQUENCE 0
#define SPACE_SEQUENCE 1

extern int tabstop; /* size of a tab */

int main()
{
    if (tabstop == 1) /* not replacement performed if */
	return 0;     /* tabstop is 1. i.e. if tab is the same 
	                 as a space. 
		       */

    int c, state, num_spaces; 

    state = CHAR_SEQUENCE;
    num_spaces = 0; 

    while ((c = getchar()) != EOF) {
	if (state == CHAR_SEQUENCE) {
	    if (c == ' ') {
		state = SPACE_SEQUENCE; 
		num_spaces = 1; 
	    } else 
		putchar(c); 	    
	} else {
	    if (c == ' ') {
		num_spaces++; 
		if (num_spaces == tabstop) {
		    putchar('\t'); 
		    num_spaces = 0; 
		}
	    } else {
		for ( ; num_spaces > 0; num_spaces--)
		    putchar(' '); 
		state = CHAR_SEQUENCE; 
		putchar(c); 
	    }
	}
    }
    return 0; 
}


