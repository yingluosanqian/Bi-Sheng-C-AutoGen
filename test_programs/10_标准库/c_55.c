/*
10_标准库.md
使用RefCell实现惰性初始化
*/
#include <stdio.h>
#include <stdlib.h>

struct LazyValue {
    int initialized;
    int value;
};

void init_lazy(struct LazyValue* lv, int val) {
    if (!lv->initialized) {
        lv->value = val;
        lv->initialized = 1;
    }
}

int main(void) {
    struct LazyValue lv = {0};
    init_lazy(&lv, 42);
    printf("Value: %d\n", lv.value);
    return 0;
}