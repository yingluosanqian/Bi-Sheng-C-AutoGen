/*
0_成员函数.md
为struct Student添加print_info成员函数，打印学生信息
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define Student structure
struct Student {
    char name[50];
    int age;
    float gpa;
};

// In standard C, we need to define functions that operate on structs separately
void print_info(struct Student* student) {
    printf("Student Information:\n");
    printf("Name: %s\n", student->name);
    printf("Age: %d\n", student->age);
    printf("GPA: %.2f\n", student->gpa);
}

int main() {
    // Create a student
    struct Student student;
    
    // Initialize student data
    strcpy(student.name, "John Doe");
    student.age = 20;
    student.gpa = 3.75;
    
    // Print student information using the function
    print_info(&student);
    
    return 0;
}
