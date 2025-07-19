/*
1_泛型.md
泛型结构体实现范围，支持不同类型的起始结束值
*/
#include <stdio.h>

// In C, we need separate struct definitions for each type combination
struct IntRange {
    int start;
    int end;
};

struct FloatRange {
    float start;
    float end;
};

// Check if value is within int range
int int_in_range(struct IntRange *range, int value) {
    return (value >= range->start && value < range->end);
}

// Check if value is within float range
int float_in_range(struct FloatRange *range, float value) {
    return (value >= range->start && value < range->end);
}

int main() {
    // Create an integer range from 10 to 20
    struct IntRange int_range = {10, 20};
    
    // Create a float range from 1.5 to 3.5
    struct FloatRange float_range = {1.5, 3.5};
    
    // Check if values are in range
    printf("Is 15 in int range? %s\n", int_in_range(&int_range, 15) ? "Yes" : "No");
    printf("Is 25 in int range? %s\n", int_in_range(&int_range, 25) ? "Yes" : "No");
    printf("Is 2.5 in float range? %s\n", float_in_range(&float_range, 2.5) ? "Yes" : "No");
    printf("Is 4.0 in float range? %s\n", float_in_range(&float_range, 4.0) ? "Yes" : "No");
    
    return 0;
}