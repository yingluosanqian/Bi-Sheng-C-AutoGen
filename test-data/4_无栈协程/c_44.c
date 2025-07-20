/*
4_无栈协程.md
async函数处理图像处理模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct Pixel {
    unsigned char r, g, b;
};

struct Pixel grayscale(struct Pixel p) {
    unsigned char gray = (p.r + p.g + p.b) / 3;
    return (struct Pixel){gray, gray, gray};
}

int main() {
    struct Pixel input = {100, 150, 200};
    struct Pixel output = grayscale(input);
    
    printf("{\"r\":%d,\"g\":%d,\"b\":%d}", output.r, output.g, output.b);
    return 0;
}