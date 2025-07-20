/*
8_运算符重载.md
重载*运算符实现向量点积
*/
#include <stdio.h>

struct Vector {
    int data[3];
};

int vector_dot(struct Vector v1, struct Vector v2) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += v1.data[i] * v2.data[i];
    }
    return sum;
}

int main() {
    struct Vector v1 = {{1, 2, 3}};
    struct Vector v2 = {{4, 5, 6}};
    int result = vector_dot(v1, v2);
    printf("%d\n", result);
    return 0;
}