#include <stdio.h>

int simple_if(int a) {
    if (a > 0) {
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int result = simple_if(5);
    printf("Result: %d\n", result);
    return result;
}