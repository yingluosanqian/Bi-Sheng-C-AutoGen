/*
4_无栈协程.md
async函数处理用户登录模拟
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_success;
    char username[50];
} LoginResult;

void fake_db_query(const char* username, const char* password, void (*callback)(LoginResult*)) {
    LoginResult* result = malloc(sizeof(LoginResult));
    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        result->is_success = 1;
        strcpy(result->username, username);
    } else {
        result->is_success = 0;
        strcpy(result->username, "");
    }
    callback(result);
    free(result);
}

void login_callback(LoginResult* result) {
    printf("{\"success\":%d,\"username\":\"%s\"}", 
           result->is_success, result->username);
}

int main() {
    fake_db_query("admin", "1234", login_callback);
    return 0;
}