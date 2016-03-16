/* Example in Section 4.3
   Exercise 4-3
   Exercise 4-4: For exercise 4-4, the following capital case letters
   are introduced for commands
   - 'T' for printing top of stack
   - 'D' for duplicating top of stack
   - 'S' for swaping the top two elements
   - 'C' for clearing the stack
 */

#include <stdio.h>
#include <stdlib.h> /* for atof */

#define MAXOP  100  /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define LIBFUNC '1' /* signal that a library function was found */
#define TOP 'T'
#define DUPLICATE 'D'
#define SWAPTOP 'S'
#define CLEAR 'C'

int getop(char []); 
void push(double); 
double pop(void); 
double top(void); 
void duplicate(void); 
void swaptop(void);
void clear(void); 
void printstack(); 
void printbuf(); 

/* reverse Polish calculator */ 
/* Exercise 4-3: added % operator */
int main () 
{
    int type; 
    double op2; 
    char s[MAXOP]; 

    while ((type = getop(s)) != EOF) {
	switch (type) {
	case NUMBER:
	    push(atof(s)); 
	    break; 
	case '+':
	    push(pop() + pop()); 
	    break; 
	case '*':
	    push(pop() * pop()); 
	    break; 
	case '-':
	    op2 = pop(); 
	    push(pop() - op2); 
	    break; 
	case '/':
	    op2 = pop(); 
	    if (op2 != 0.0)
		push(pop() / op2); 
	    else
		printf("error:zero divisor\n"); 
	    break; 
	case '%':
	    op2 = pop(); 
	    if (op2 != 0.0)
		push((int)pop() % (int)op2); 
	    else
		printf("error:zero divisor in modulus calculation\n"); 
	    break; 
	case TOP:
	    printf("Top: \t%.8g\n", top()); 
	    break; 
	case DUPLICATE:
	    duplicate(); 
	    break; 
	case SWAPTOP:
	    swaptop(); 
	    break; 
	case CLEAR:
	    clear(); 
	    break; 
	case '\n':
	    printf("\t%.8g\n", pop()); 
	    break; 
	default:
	    printf("error: unknown command %s\n", s); 
	}
    }
    return 0; 
}

/*********************************************************************/
/* push and pop */ 
#define MAXVAL 100  /* maximum depth of val stack */ 

int sp = 0;         /* next free stack position */ 
double val[MAXVAL]; /* value stack */ 

/* push: push f onto value stack */ 
void push(double f)
{
    if (sp < MAXVAL)
	val[sp++] = f; 
    else
	printf("error: stack full, can't push %g\n", f); 
}

/* pop: pop and return top value from stack */ 
double pop(void)
{
    if (sp > 0)
	return val[--sp]; 
    else {
	printf("error: stack empty\n"); 
	return 0.0; 
    }
}

/* function to debug the stack */
void printstack()
{
    printf("Current stack:\t"); 
    for (int i = 0; i < sp; i++)
	printf("%f\t", val[i]); 
    printf("\n"); 
}

/* top: return the top of the stack */
double top(void)
{
    double f = pop(); /* make sure error check is performed */
    push(f); 
    return f; 
}

/* duplicate: duplicate the top element of the stack */
void duplicate(void)
{
    double f = top(); 
    push(f); 
}

/* swaptop: swap the top two elements of the stack */
void swaptop(void)
{
    double f = pop(); 
    double g = pop(); 
    push(f); 
    push(g); 
}

/* clear: clear the stack */
void clear(void)
{
    sp = 0; 
}

/*********************************************************************/

/*********************************************************************/
/* getop: get next operator or numeric operand */
#include <ctype.h>
#define MATCH    1
#define NO_MATCH 0

int getch(void); 
void ungetch(int); 
void ungets(char[]); /* Exercisr 4-7 */
int match(char[]); 

/* Exercise 4-3, added provision for negative numbers */
int getop(char s[])
{
    int i, c; 

    while ((s[0] = c = getch()) == ' ' || c == '\t')
	; 
    s[1] = '\0'; 
    if (!isdigit(c) && c != '.' && c != '-')
	return c; /* not a number */
    
    if (c == '-') {
	if (!isdigit(c = getch())) {  /* if the '-' is minus */
	    ungetch(c);  
	    return '-'; 
	} else                        /* if the '-' is the negative sign */
	    ungetch(c);
    }

    i = 0; 
    if (isdigit(c)) /* collect integer part */
	while (isdigit(s[++i] = c = getch()))
	    ;
    if (c == '.')
	while (isdigit(s[++i] = c = getch())) /* collect the fraction part */
	    ; 
    s[i] = '\0'; 

    if (c != EOF)
	ungetch(c); 
    return NUMBER; 
}

/* match(p): match the given string pattern p from the input
   returns 1 if the pattern specified is matched, 0 if not matched. 
   If the pattern is matched, the input pointer is moved to the character
   right after the matched pattern, otherwise the input pointer is reset 
   to the value before this function is called. This behaviour is implemented
   by calling ungets to push the unmatched pattern back into the buffer. 
 */ 
int match(char p[])
{
    char s[MAXOP]; 
    int state = MATCH; 
    for (int i = 0; p[i] != '\0'; i++) {
	s[i] = getch(); 
	if (s[i] != p[i]) {
	    state = NO_MATCH;
	    break; 
	}
    }

    if (state == NO_MATCH)
	ungets(s); 

    return state; 
}

/*********************************************************************/

/*********************************************************************/
/* getch and ungetch */
#include <string.h>
#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
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

/* Exercise 4-7 */
/* ungets(s): put an entire string back into the buffer */
void ungets(char s[])
{
    for (int i = strlen(s) - 1; i >= 0; i--) {
	printf("%d\t", i); 
	ungetch(s[i]); 
    }
}

/* function to debug the buf */
void printbuf()
{
    printf("Current buf:\t"); 
    for (int i = 0; i < bufp; i++)
	printf("%c\t", buf[i]); 
    printf("\n"); 
}

/*********************************************************************/
