/*
7_owned-struct-类型.md
定义owned struct Student，包含id和grade成员
*/
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    int grade;
};

void print_student(struct Student *s) {
    printf("Student ID: %d, Grade: %d\n", s->id, s->grade);
}

int main() {
    struct Student s = {.id = 12345, .grade = 90};
    print_student(&s);
    return 0;
}