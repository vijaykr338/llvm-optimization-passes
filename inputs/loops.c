#include <stdio.h>

int for_loop_example(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += i;
    }
    return sum;
}

int while_loop_example(int n) {
    int sum = 0;
    int i = 0;
    while (i < n) {
        sum += i;
        i++;
    }
    return sum;
}

int nested_loops(int n, int m) {
    int result = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            result += i * j;
        }
    }
    return result;
}

int main() {
    int a = for_loop_example(5);
    int b = while_loop_example(5);
    int c = nested_loops(3, 4);
    
    printf("Results: %d, %d, %d\n", a, b, c);
    return 0;
}