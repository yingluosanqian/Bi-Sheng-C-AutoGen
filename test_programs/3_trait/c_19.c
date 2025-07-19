/*
3_trait.md
trait指针变量的强制类型转换为具体类型指针
*/
#include <stdio.h>
#include <stdlib.h>

struct Square {
    int side;
};

int main() {
    struct Square s = {5};
    struct Square* square_ptr = &s;
    void* void_ptr = (void*)square_ptr;
    struct Square* casted_ptr = (struct Square*)void_ptr;
    
    printf("%d\n", casted_ptr->side);
    return 0;
}