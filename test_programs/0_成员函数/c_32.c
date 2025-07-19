/*
0_成员函数.md
为struct Triangle添加is_valid成员函数，验证三角形有效性
*/
#include <stdio.h>
#include <stdbool.h>

struct Triangle {
    double a;
    double b;
    double c;
};

bool is_triangle_valid(struct Triangle* t) {
    return (t->a + t->b > t->c) &&
           (t->a + t->c > t->b) &&
           (t->b + t->c > t->a);
}

int main() {
    struct Triangle t1 = {3, 4, 5};
    struct Triangle t2 = {1, 2, 5};
    
    printf("Triangle 1 is %s\n", is_triangle_valid(&t1) ? "valid" : "invalid");
    printf("Triangle 2 is %s\n", is_triangle_valid(&t2) ? "valid" : "invalid");
    
    return 0;
}
