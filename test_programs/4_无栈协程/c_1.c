/*
4_无栈协程.md
async函数等待另一个async函数完成
*/
#include <stdio.h>
#include <stdlib.h>

/* Standard C doesn't support async/await - this is just a synchronous simulation */
int timeOut(int t) {
    return t;
}

int getData() {
    int t = timeOut(1000);
    return t;
}

int main() {
    int result = getData();
    printf("%d", result);
    return 0;
}