/*
4_无栈协程.md
async函数处理用户注销模拟
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int is_logged_in;
} User;

void logout(User* user) {
    user->is_logged_in = 0;
    printf("{\"status\": \"logged_out\"}");
}

int main() {
    User user = {1};
    void (*logout_func)(User*) = logout;
    logout_func(&user);
    return 0;
}