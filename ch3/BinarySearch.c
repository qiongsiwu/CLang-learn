/* Exercise 3-1 */ 

#include <stdio.h>
#define MAX_SIZE 1024

int binsearch(int x, int v[], int n); 

int main()
{
    printf("Hello world\n"); 
    int a1[MAX_SIZE]; 
    
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid; 
    
    low = 0; 
    high = n - 1; 
    while (low <= high) {
	mid = (low + high) / 2; 
	if (x < v[mid])
	    high = mid - 1; 
	else if (x > v[mid])
	    low = mid + 1; 
	else /* found match */
	    return mid; 
    }
    return -1; /* not match */ 
} 
