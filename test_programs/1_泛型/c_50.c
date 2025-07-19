/*
1_泛型.md
泛型函数实现字符串比较，支持不同字符类型
*/
#include <stdio.h>
#include <string.h>
#include <wchar.h>

// Function for comparing char strings
int compare_char_string(const char *str1, const char *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

// Function for comparing wchar_t strings
int compare_wchar_string(const wchar_t *str1, const wchar_t *str2) {
    while (*str1 && (*str1 == *str2)) {
        str1++;
        str2++;
    }
    return *str1 - *str2;
}

int main() {
    char str1[] = "hello";
    char str2[] = "world";
    wchar_t wstr1[] = L"hello";
    wchar_t wstr2[] = L"world";
    
    int result1 = compare_char_string(str1, str2);
    int result2 = compare_wchar_string(wstr1, wstr2);
    
    printf("%d\n", result1 < 0 ? -1 : (result1 > 0 ? 1 : 0));
    printf("%d\n", result2 < 0 ? -1 : (result2 > 0 ? 1 : 0));
    
    return 0;
}