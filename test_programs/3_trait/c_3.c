/*
3_trait.md
为struct Student实现Serializable trait，支持序列化
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function pointer type for serialization
typedef void (*SerializeFunc)(void*);

typedef struct {
    char name[50];
    int age;
    float gpa;
    SerializeFunc serialize; // Function pointer for serialization
} Student;

// Serialization function for Student
void student_serialize(Student* this) {
    printf("Serializing Student:\n");
    printf("  Name: %s\n", this->name);
    printf("  Age: %d\n", this->age);
    printf("  GPA: %.2f\n", this->gpa);
}

// Constructor for Student
Student* create_student(const char* name, int age, float gpa) {
    Student* s = malloc(sizeof(Student));
    strncpy(s->name, name, sizeof(s->name)-1);
    s->age = age;
    s->gpa = gpa;
    s->serialize = (SerializeFunc)student_serialize;
    return s;
}

int main() {
    // Create and serialize a student
    Student* s = create_student("Alice", 20, 3.8);
    s->serialize(s);
    
    free(s);
    return 0;
}
