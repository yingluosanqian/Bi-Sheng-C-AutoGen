/*
7_owned-struct-类型.md
创建owned struct Student实例并初始化id和grade
*/
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    float grade;
};

int main() {
    struct Student s = {.id = 12345, .grade = 89.5};
    printf("Student ID: %d, Grade: %.1f\n", s.id, s.grade);
    return 0;
}