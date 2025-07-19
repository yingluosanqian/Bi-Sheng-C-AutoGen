/*
2_常量计算.md
constexpr if实现不同数据类型的统一处理接口
*/
#include <stdio.h>

/* Standard C requires separate functions for different types */
void process_int(int value) {
    printf("Processing integer: %d\n", value * 2);
}

void process_float(float value) {
    printf("Processing float: %.2f\n", value * 2.0f);
}

/* Function pointer approach for unified interface */
typedef void (*processor_func)(void* value);

void int_processor(void* value) {
    int val = *(int*)value;
    printf("Processing integer: %d\n", val * 2);
}

void float_processor(void* value) {
    float val = *(float*)value;
    printf("Processing float: %.2f\n", val * 2.0f);
}

void process_value(void* value, processor_func processor) {
    processor(value);
}

int main() {
    int int_val = 21;
    float float_val = 10.5f;
    
    process_value(&int_val, int_processor);
    process_value(&float_val, float_processor);
    
    return 0;
}