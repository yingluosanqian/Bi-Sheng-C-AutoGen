/*
3_trait.md
结构体实现多个不同泛型trait的组合使用
*/
#include <stdio.h>

/* In standard C, we simulate traits with function pointers */
struct Calculator {
    int (*add)(struct Calculator* this, int x);
    int (*multiply)(struct Calculator* this, int x);
};

struct Printer {
    void (*print)(struct Printer* this);
};

struct Number {
    int value;
    struct Calculator calc;
    struct Printer printer;
};

int Number_add(struct Number* this, int x) {
    return this->value + x;
}

int Number_multiply(struct Number* this, int x) {
    return this->value * x;
}

void Number_print(struct Number* this) {
    printf("Value: %d\n", this->value);
}

void initNumber(struct Number* num, int value) {
    num->value = value;
    num->calc.add = (int (*)(struct Calculator*, int))Number_add;
    num->calc.multiply = (int (*)(struct Calculator*, int))Number_multiply;
    num->printer.print = (void (*)(struct Printer*))Number_print;
}

int main() {
    struct Number num;
    initNumber(&num, 5);
    
    num.printer.print((struct Printer*)&num);
    int sum = num.calc.add((struct Calculator*)&num, 3);
    int product = num.calc.multiply((struct Calculator*)&num, 4);
    
    printf("Sum: %d, Product: %d\n", sum, product);
    return 0;
}