/*
7_owned-struct-类型.md
47. Create owned struct 'EmployeeRecord' with position and salary
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct EmployeeRecord {
    char position[50];
    int salary;
};

void printEmployee(struct EmployeeRecord *emp) {
    printf("Position: %s\nSalary: %d\n", emp->position, emp->salary);
}

int main() {
    struct EmployeeRecord emp = {
        .position = "Software Engineer",
        .salary = 100000
    };
    
    printEmployee(&emp);
    
    return 0;
}