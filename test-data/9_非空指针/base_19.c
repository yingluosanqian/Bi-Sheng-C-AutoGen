/* Pointer to a Function */
#include <stdio.h>

void greet() {
    printf("{result: Executed via function pointer}\n");
}

int main() {
    void (*func_ptr)() = &greet;
    func_ptr();
    return 0;
}