/*
3_trait.md
Animal trait为Dog和Cat结构体实现makeSound方法
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Dog {
    const char* sound;
} Dog;

typedef struct Cat {
    const char* sound;
} Cat;

void Dog_makeSound(Dog* this) {
    printf("%s\n", this->sound);
}

void Cat_makeSound(Cat* this) {
    printf("%s\n", this->sound);
}

int main() {
    Dog dog = {"Woof"};
    Cat cat = {"Meow"};
    
    Dog_makeSound(&dog);
    Cat_makeSound(&cat);
    
    return 0;
}