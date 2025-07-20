/*
0_成员函数.md
为float类型添加to_string成员函数，转换为字符串
*/
#include <stdio.h>
#include <stdlib.h>

// Standard C needs a global function to convert float to string
char* float_to_string(float value, int precision) {
    // Allocate memory for the result
    char* buffer = (char*)malloc(32);
    if (buffer == NULL) {
        return NULL;
    }
    
    // Use sprintf to convert float to string
    sprintf(buffer, "%.*f", precision, value);
    
    return buffer;
}

int main() {
    float number = 123.456;
    
    // In standard C, we call the global function
    char* str = float_to_string(number, 2);
    printf("The float %f as string: %s\n", number, str);
    
    // Clean up
    free(str);
    
    return 0;
}
