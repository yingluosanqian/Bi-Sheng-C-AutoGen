/*
8_运算符重载.md
重载<运算符比较两个学生的成绩
*/
#include <stdio.h>

struct Student {
    char name[20];
    int score;
};

int compareStudents(struct Student s1, struct Student s2) {
    return s1.score < s2.score;
}

int main() {
    struct Student alice = {"Alice", 85};
    struct Student bob = {"Bob", 92};
    
    printf("%d\n", compareStudents(alice, bob));
    return 0;
}