#include <stdio.h>

int complex_switch(int value) {
    int result = 0;
    
    switch (value) {
        case 1:
            result = 10;
            break;
        case 2:
        case 3:
            result = 20;
            for (int i = 0; i < value; i++) {
                result += i;
            }
            break;
        case 4:
            result = 30;
            if (value % 2 == 0) {
                result += 5;
            }
            break;
        default:
            result = value * 5;
            while (result > 50) {
                result -= 10;
            }
    }
    
    return result;
}

int nested_conditions(int a, int b) {
    if (a > 10) {
        if (b > 10) {
            return a + b;
        } else {
            return a - b;
        }
    } else {
        if (b > 5) {
            return a * b;
        } else {
            return a / (b == 0 ? 1 : b);
        }
    }
}

int main() {
    for (int i = 1; i <= 6; i++) {
        int result = complex_switch(i);
        printf("complex_switch(%d) = %d\n", i, result);
    }
    
    int nc_result = nested_conditions(15, 8);
    printf("nested_conditions(15, 8) = %d\n", nc_result);
    
    return 0;
}