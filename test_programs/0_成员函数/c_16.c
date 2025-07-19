/*
0_成员函数.md
为struct Student添加print_info成员函数，打印学生信息
*/
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    float score;
};

void print_info(struct Student* student) {
    printf("Student ID: %d, Name: %s, Score: %.2f\n", student->id, student->name, student->score);
}

int main() {
    struct Student student = {1001, "Alice", 95.5};
    print_info(&student);
    return 0;
}