/*
7_owned-struct-类型.md
创建owned struct Employee实例并初始化id和salary
*/
#include <stdio.h>
#include <stdlib.h>

struct Employee {
    int id;
    double salary;
};

void printEmployee(struct Employee *emp) {
    printf("Employee ID: %d, Salary: %.2f\n", emp->id, emp->salary);
}

int main() {
    struct Employee emp = {.id = 1001, .salary = 50000.50};
    printEmployee(&emp);
    return 0;
}