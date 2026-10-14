#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    } else {
        return n * factorial(n - 1);
    }
}

int fibonacci(int n) {
    if (n <= 1) {
        return n;
    } else {
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int fact_result = factorial(5);
    int fib_result = fibonacci(7);
    
    printf("5! = %d, fib(7) = %d\n", fact_result, fib_result);
    return 0;
}