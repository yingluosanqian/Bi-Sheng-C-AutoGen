/*
10_标准库.md
使用Rc的clone方法创建另一个共享指针
*/
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int value;
} Data;

int main() {
    Data* data = malloc(sizeof(Data));
    data->value = 42;
    
    Data* shared1 = data;
    Data* shared2 = data;
    
    printf("Value: %d\n", shared1->value);
    printf("Value: %d\n", shared2->value);
    
    free(data);
    return 0;
}