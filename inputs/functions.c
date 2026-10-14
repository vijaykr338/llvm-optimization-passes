#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int multiply(int a, int b) {
    return a * b;
}

int compute(int a, int b) {
    int sum = add(a, b);
    int result = multiply(sum, 2);
    return result;
}

int process(int x) {
    if (x < 10) {
        return add(x, 5);
    } else {
        return multiply(x, 2);
    }
}

int main() {
    int result1 = compute(3, 4);
    int result2 = add(result1, 5);
    int result3 = process(result2);
    
    printf("Final result: %d\n", result3);
    return 0;
}