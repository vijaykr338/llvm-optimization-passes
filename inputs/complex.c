#include <stdio.h>

void leaf1() {
    printf("Leaf1 function\n");
}

void leaf2() {
    printf("Leaf2 function\n");
}

void middle1() {
    leaf1();
    leaf2();
    leaf1();
}

void middle2() {
    leaf2();
    leaf2();
}

void top() {
    middle1();
    middle2();
    leaf1();
}

int main() {
    top();
    middle1();
    return 0;
}