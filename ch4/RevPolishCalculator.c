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

#define MAXOP  100 /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
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

void duplicate(void)
{
    double f = top(); 
    push(f); 
}

void swaptop(void)
{
    double f = pop(); 
    double g = pop(); 
    push(f); 
    push(g); 
}

void clear(void)
{
    sp = 0; 
}

/*********************************************************************/

/*********************************************************************/
/* getop: get next operator or numeric operand */
#include <ctype.h>

int getch(void); 
void ungetch(int); 

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

/*********************************************************************/

/*********************************************************************/
/* getch and ungetch */
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

/* function to debug the buf */
void printbuf()
{
    printf("Current buf:\t"); 
    for (int i = 0; i < bufp; i++)
	printf("%d\t", buf[i]); 
    printf("\n"); 
}

/*********************************************************************/
