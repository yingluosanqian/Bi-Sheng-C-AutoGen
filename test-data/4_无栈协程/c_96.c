/*
4_无栈协程.md
async函数处理搜索算法模拟
*/
#include <stdio.h>
#include <stdlib.h>

int search_sync(int* array, int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int main() {
    int array[] = {1, 2, 3, 4, 5};
    int size = sizeof(array)/sizeof(array[0]);
    int target = 3;
    
    int result = search_sync(array, size, target);
    
    printf("{\"result\":%d}", result);
    return 0;
}