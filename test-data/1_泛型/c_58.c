/*
1_泛型.md
泛型结构体实现可选值，支持任意类型的可空值
*/
#include <stdio.h>
#include <stdlib.h>

struct OptionalInt {
    int has_value;
    int value;
};

struct OptionalFloat {
    int has_value;
    float value;
};

struct OptionalInt create_optional_int(int value) {
    struct OptionalInt opt = {1, value};
    return opt;
}

struct OptionalFloat create_optional_float(float value) {
    struct OptionalFloat opt = {1, value};
    return opt;
}

struct OptionalInt create_empty_int() {
    struct OptionalInt opt = {0, 0};
    return opt;
}

struct OptionalFloat create_empty_float() {
    struct OptionalFloat opt = {0, 0.0f};
    return opt;
}

int main() {
    struct OptionalInt opt_int = create_optional_int(42);
    struct OptionalFloat opt_float = create_optional_float(3.14f);
    struct OptionalInt empty_int = create_empty_int();
    
    if (opt_int.has_value) {
        printf("Integer value: %d\n", opt_int.value);
    }
    
    if (opt_float.has_value) {
        printf("Float value: %.2f\n", opt_float.value);
    }
    
    if (!empty_int.has_value) {
        printf("Empty optional\n");
    }
    
    return 0;
}