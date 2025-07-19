/*
1_泛型.md
泛型结构体实现结果类型，支持成功失败两种状态
*/
#include <stdio.h>
#include <stdlib.h>

// In standard C, we need separate result types for different data types
typedef struct {
    int value;
    int is_success;
    const char* error_message;
} IntResult;

typedef struct {
    double value;
    int is_success;
    const char* error_message;
} DoubleResult;

// Functions to create success or error results
IntResult int_success(int value) {
    IntResult result;
    result.value = value;
    result.is_success = 1;
    result.error_message = NULL;
    return result;
}

IntResult int_error(const char* message) {
    IntResult result;
    result.value = 0;
    result.is_success = 0;
    result.error_message = message;
    return result;
}

DoubleResult double_success(double value) {
    DoubleResult result;
    result.value = value;
    result.is_success = 1;
    result.error_message = NULL;
    return result;
}

DoubleResult double_error(const char* message) {
    DoubleResult result;
    result.value = 0.0;
    result.is_success = 0;
    result.error_message = message;
    return result;
}

// Example functions that return results
IntResult divide_ints(int a, int b) {
    if (b == 0) {
        return int_error("Division by zero");
    }
    return int_success(a / b);
}

DoubleResult divide_doubles(double a, double b) {
    if (b == 0.0) {
        return double_error("Division by zero");
    }
    return double_success(a / b);
}

int main() {
    // Integer division example
    IntResult int_result1 = divide_ints(10, 2);
    if (int_result1.is_success) {
        printf("Int division result: %d\n", int_result1.value);
    } else {
        printf("Int division error: %s\n", int_result1.error_message);
    }
    
    IntResult int_result2 = divide_ints(10, 0);
    if (int_result2.is_success) {
        printf("Int division result: %d\n", int_result2.value);
    } else {
        printf("Int division error: %s\n", int_result2.error_message);
    }
    
    // Double division example
    DoubleResult double_result1 = divide_doubles(10.0, 2.0);
    if (double_result1.is_success) {
        printf("Double division result: %.1f\n", double_result1.value);
    } else {
        printf("Double division error: %s\n", double_result1.error_message);
    }
    
    DoubleResult double_result2 = divide_doubles(10.0, 0.0);
    if (double_result2.is_success) {
        printf("Double division result: %.1f\n", double_result2.value);
    } else {
        printf("Double division error: %s\n", double_result2.error_message);
    }
    
    return 0;
}