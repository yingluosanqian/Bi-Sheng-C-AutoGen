/*
0_成员函数.md
为char类型添加is_alpha成员函数，判断是否为字母字符
*/
#include <stdio.h>
#include <ctype.h>

int main() {
    char test_chars[] = {'a', 'Z', '5', '@', 'm'};
    int num_chars = sizeof(test_chars) / sizeof(test_chars[0]);
    
    printf("Character alpha check results:\n");
    
    for (int i = 0; i < num_chars; i++) {
        char ch = test_chars[i];
        int result = isalpha(ch);
        printf("'%c': %s\n", ch, result ? "true" : "false");
    }
    
    return 0;
}