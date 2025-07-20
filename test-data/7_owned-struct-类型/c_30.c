/*
7_owned-struct-类型.md
31. Define owned struct 'StudentRecord' with grades array
*/
#include <stdio.h>
#include <stdlib.h>

struct StudentRecord {
    char name[50];
    int id;
    float grades[5];
};

void print_student(struct StudentRecord student) {
    printf("Student: %s (ID: %d)\n", student.name, student.id);
    printf("Grades: ");
    for (int i = 0; i < 5; i++) {
        printf("%.1f ", student.grades[i]);
    }
    printf("\n");
}

int main() {
    struct StudentRecord student = {
        .name = "Alice Johnson",
        .id = 1001,
        .grades = {85.5, 90.0, 78.5, 92.0, 88.5}
    };
    
    print_student(student);
    
    return 0;
}