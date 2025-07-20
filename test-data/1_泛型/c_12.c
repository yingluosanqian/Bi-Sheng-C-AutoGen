/*
1_泛型.md
泛型结构体实现三元组，存储三个任意类型的值
*/
#include <stdio.h>
#include <stdlib.h>

/* Separate struct definitions for different type combinations */
struct IntTriplet {
    int first;
    int second;
    int third;
};

struct FloatTriplet {
    float first;
    float second;
    float third;
};

struct MixedTriplet {
    int first;
    float second;
    char third;
};

/* Separate functions for each struct type */
void print_int_triplet(struct IntTriplet *triplet) {
    printf("(%d, %d, %d)\n", triplet->first, triplet->second, triplet->third);
}

void print_float_triplet(struct FloatTriplet *triplet) {
    printf("(%.1f, %.1f, %.1f)\n", triplet->first, triplet->second, triplet->third);
}

void print_mixed_triplet(struct MixedTriplet *triplet) {
    printf("(%d, %.1f, %c)\n", triplet->first, triplet->second, triplet->third);
}

int main() {
    struct IntTriplet int_triplet = {1, 2, 3};
    struct FloatTriplet float_triplet = {1.5, 2.5, 3.5};
    struct MixedTriplet mixed_triplet = {42, 3.14, 'A'};
    
    print_int_triplet(&int_triplet);
    print_float_triplet(&float_triplet);
    print_mixed_triplet(&mixed_triplet);
    
    return 0;
}