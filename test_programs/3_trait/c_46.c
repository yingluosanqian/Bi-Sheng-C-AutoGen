/*
3_trait.md
泛型trait Generator生成序列值
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In standard C, we simulate traits using function pointers
struct Generator {
    void* state;
    void* (*next)(void*);
};

// Integer generator implementation
int* int_next(void* state) {
    int* count = (int*)state;
    (*count)++;
    return count;
}

struct Generator create_int_generator(int start) {
    int* state = malloc(sizeof(int));
    *state = start - 1; // We'll increment before returning
    return (struct Generator){
        .state = state,
        .next = int_next
    };
}

// String generator implementation
const char** string_next(void* state) {
    const char*** strings = (const char***)state;
    (*strings)++;
    return *strings;
}

struct Generator create_string_generator(const char** strings) {
    const char*** state = malloc(sizeof(const char**));
    *state = strings - 1; // We'll increment before returning
    return (struct Generator){
        .state = state,
        .next = string_next
    };
}

void free_generator(struct Generator gen) {
    free(gen.state);
}

int main() {
    // Integer generator
    struct Generator int_gen = create_int_generator(5);
    for (int i = 0; i < 3; i++) {
        printf("Next int: %d\n", *(int*)int_gen.next(int_gen.state));
    }
    free_generator(int_gen);

    // String generator
    const char* words[] = {"hello", "world", "generator", NULL};
    struct Generator str_gen = create_string_generator(words);
    for (int i = 0; i < 3; i++) {
        printf("Next string: %s\n", *(const char**)str_gen.next(str_gen.state));
    }
    free_generator(str_gen);

    return 0;
}
