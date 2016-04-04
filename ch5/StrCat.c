/* Exercise 5-3 */

#include <stdio.h>
#define MAX_LEN 1024

void strcat_p(char *, char *); 

int main()
{
    printf("Hello world!\n"); 
    char s_1[MAX_LEN] = "A"; 
    char t_1[MAX_LEN / 2] = " is on the tree. "; 
    strcat_p(s_1, t_1); 
    printf("s + t is : %s \n", s_1); 
}

/* strcat_p: concatenate t to end of s; s must be big enough */ 
/* uses pointer arithmetic */
void strcat_p(char *s, char *t)
{
    while (*s) 
	s++; 
    while ((*s++ = *t++)) 
	;
}
