/*
3_trait.md
定义Empty trait（无方法），为多个类型实现空trait
*/
#include <stdio.h>

/* In standard C, we simulate traits using function pointers */
struct EmptyTrait {
    /* No methods - empty trait */
};

struct MyType1 { int value; };
struct MyType2 { float value; };

int main() {
    struct MyType1 t1 = {42};
    struct MyType2 t2 = {3.14f};
    
    /* In C, we can't really do anything with empty traits */
    return 0;
}