/*
4_无栈协程.md
async函数实现简单的登录验证
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct LoginResult {
    int success;
    char message[50];
};

struct LoginResult verify_login(const char* username, const char* password) {
    struct LoginResult result;
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        result.success = 1;
        strcpy(result.message, "Login successful");
    } else {
        result.success = 0;
        strcpy(result.message, "Invalid credentials");
    }
    return result;
}

int main() {
    struct LoginResult result = verify_login("admin", "1234");
    printf("{\"success\":%d,\"message\":\"%s\"}", result.success, result.message);
    return 0;
}