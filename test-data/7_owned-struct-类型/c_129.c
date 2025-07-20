/*
7_owned-struct-类型.md
创建owned struct Component实例并初始化type和data
*/
#include <stdio.h>
#include <stdlib.h>

struct Component {
    int type;
    char data[32];
};

int main() {
    struct Component comp = {
        .type = 42,
        .data = "Sample component data"
    };
    
    printf("Component type: %d\n", comp.type);
    printf("Component data: %s\n", comp.data);
    
    return 0;
}