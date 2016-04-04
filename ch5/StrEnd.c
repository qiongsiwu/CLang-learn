/* Exercise 5-4 */

#include <stdio.h>
#include <string.h>

int strend(char *, char *); 

int main () 
{
    printf("end? %d\n", strend("This", "is")); 
    printf("end? %d\n", strend("This", "are")); 
    printf("end? %d\n", strend("I", "It")); 
    printf("end? %d\n", strend("It", "I")); 
    printf("end? %d\n", strend("These", "These")); 
}

/* strend: returns 
   - 1 if the string t occurs at the end of the 
     string s. 
   - 0 otherwise. 
*/ 
int strend(char *s, char *t)
{
    int slen = strlen(s); 
    int tlen = strlen(t); 
    
    if (slen >= tlen) {
	s = s + (slen - tlen); 
	for ( ; *s == *t; s++, t++) {
	    if (!*s)
		return 1; 
	}
	return 0; 
    } else {
	return 0; 
    }
}
