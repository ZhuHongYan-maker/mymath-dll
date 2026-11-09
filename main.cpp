
#include <stdio.h>
#include "mymath.h"
int add(int a, int b){return a + b;}
int div(int a, int b) { return b != 0 ? a / b : 0; }
int mul(int a, int b) { return a * b; }	
int sub(int a, int b) { return a - b; }
int main() {
    int a = 20262814, b = 10;
    printf("a = %d\n",a);
    printf("b = %d\n",b);
    printf("%d+%d=%d\n", a, b, add(a, b));
    printf("%d-%d=%d\n", a, b, sub(a, b));
    printf("%d*%d=%d\n", a, b, mul(a, b));
    printf("%d/%d=%d\n", a, b, div(a, b));
    return 0;
}