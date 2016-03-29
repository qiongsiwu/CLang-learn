/* Exercise 4-14 */

#include <stdio.h>
#define swap(t, x, y) { t s; s = x; x = y; y = s;}

int main()
{
    printf("Hello world!\n");
    int a = 2; int b = 1; 
    swap(int, a, b); 
    printf("%d, %d\n", a, b); 
    char c = 'm'; char d = '!'; 
    swap(char, c, d); 
    printf("%c, %c\n", c, d); 
    double e = 3.14; double f = 6.28; 
    swap(double, e, f); 
    printf("%f, %f\n", e, f); 
}
