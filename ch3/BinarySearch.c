/* Exercise 3-1 */ 

/* Two implementations of binsearch 
   binsearch does 3 comparisons inside the while loop
   binsearch2 does 2 comparisons inside the while loop with
   an extra check at the end. 
   
   The two do not exhibit significan run time differences. 
*/

#include <stdio.h>
#include <time.h>
#define MAX_SIZE 1024
#define NUM_ITERATION 2048

int binsearch(int x, int v[], int n); 
int binsearch2(int x, int v[], int n); 

int main()
{
    printf("Hello world\n"); 
    int a1[MAX_SIZE]; 
    for (int i = 0; i < MAX_SIZE; i++)
	a1[i] = i; // initialize a sorted array

    /* testing consistency of the two search algorithms */
    int success = 1; 
    for (int j = -1; j < NUM_ITERATION; j++) {
	int idx1 = binsearch(j, a1, MAX_SIZE);
	int idx2 = binsearch2(j, a1, MAX_SIZE); 

	if (idx1 != idx2) {
	    success = 0; 
	    printf("Searched failed at value %d!\n", j); 
	    break; 
	}
    }

    if (success)
	printf("Success!\n"); 

    /* testing the run time of the two search algorithms */ 
    clock_t begin, end; 

    /* time the binsearch */ 
    int result[NUM_ITERATION + 1]; 
    begin = clock(); 
    for (int j = -1; j < NUM_ITERATION; j++) {
	result[j + 1] = binsearch(j, a1, MAX_SIZE); 
    }
    end = clock(); 
    printf("Time for binsearch: %ld\n", end - begin); 

    /* time binsearch2 */
    int result2[NUM_ITERATION + 1]; 
    begin = clock(); 
    for (int j = -1; j < NUM_ITERATION; j++) {
	result2[j + 1] = binsearch(j, a1, MAX_SIZE); 
    }
    end = clock();
    printf("Time for binsearch2: %ld\n", end - begin);   

    /* use the results to test for consistency again */
    for (int j = -1; j < NUM_ITERATION; j++) {
	if (result[j + 1] != result2[j + 1])
	    printf("Something is wrong at %d!\n", j); 
    }
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

/* binsearch2: use only two comparisons in the while */ 
int binsearch2(int x, int v[], int n)
{
    int low, high, mid; 

    low = 0; 
    high = n - 1; 
    while (low < high) {
	mid = (low + high) / 2; 
	if (x <= v[mid])
	    high = mid; 
	else
	    low = mid + 1; 
    }

    if (x == v[high])
	return high; 
    else
	return -1; 
}
