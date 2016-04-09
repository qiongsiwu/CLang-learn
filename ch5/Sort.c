#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 5000 /* max #lines to be sorted */
#define MAXLEN 1000   /* max length of line */

char *lineptr[MAXLINES]; /* pointers to text lines */
char linearray[MAXLINES * MAXLEN]; 

int readlines(char *lineptr[], int nlines); 
int readlines2(char *lineptr[], int nlines); 
void writelines(char *lineptr[], int nlines); 

void qsort(char *lineptr[], int left, int right); 

/*sort input lines */
int main() 
{
    int nlines; /* number of input lines read */

    clock_t begin, end; 
    begin = end = clock();

    if ((nlines = readlines2(lineptr, MAXLINES)) >= 0) {
	qsort(lineptr, 0, nlines - 1); 
	writelines(lineptr, nlines); 
	end = clock(); 
	printf("# clock tickes: %lu \n", end - begin); 
	return 0; 
    } else {
	printf("error: input too big to sort.\n"); 
	return 1; 
    }
}

int getline(char *, int); 
char *alloc(int); 

/* readline: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines; 
    char *p, line[MAXLEN]; 

    nlines = 0; 
    while ((len = getline(line, MAXLEN)) > 0)
	if (nlines >= maxlines || (p = alloc(len)) == NULL) 
	    return -1; 
	else {
	    line[len - 1] = '\0'; /* delete newline */
	    strcpy(p, line); 
	    lineptr[nlines++] = p; 
	}
    return nlines; 
}

/* Exercise 5-7 */
/* fastreadlines: read line but do not allocate memory */ 
int readlines2(char *lineptr[], int maxlines)
{
    int len, nlines; 
    char *line = linearray; 
 
    nlines = 0; 
    while ((len = getline(line, MAXLEN)) > 0) {
	if (nlines >= maxlines) 
	    return -1; 
	else {
	    line[len - 1] = '\0'; /* delete newline */
	    lineptr[nlines++] = line; 
	    line += len;
	}
    }
    return nlines; 
}

/* write lines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i; 

    for (i = 0; i < nlines; i++)
	printf("%s\n", lineptr[i]); 
}

/* getline: read a line into s, return the length of the string
 */
int getline(char *s, int lim)
{
    int i; 
    
    for (i=0; i<lim-1 && (*s=getchar())!=EOF && *s!='\n';++s, ++i)
	; 
    if (*s++ == '\n') {
	++i; 
    }

    *s = '\0';

    return i; 
}

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last; 
    void swap(char *v[], int i, int j); 
    
    if (left >= right) /* do nothing if array contains */
	return;        /* fewer than two elements */
    swap(v, left, (left + right)/2); 
    last = left; 
    for (i = left + 1; i <= right; i++)
	if (strcmp(v[i], v[left]) < 0)
	    swap(v, ++last, i); 
    swap(v, left, last); 
    qsort(v, left, last - 1); 
    qsort(v, last + 1, right); 
}

/* swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp; 
    
    temp = v[i]; 
    v[i] = v[j]; 
    v[j] = temp; 
}
