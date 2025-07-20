/*
1_泛型.md
泛型类型别名定义哈希映射类型，简化复杂类型声明
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Simple hash map structure for int->int mapping
struct IntIntHashMap {
    int *keys;
    int *values;
    int size;
    int capacity;
};

// Simple hash map structure for int->float mapping
struct IntFloatHashMap {
    int *keys;
    float *values;
    int size;
    int capacity;
};

// Initialize int->int hash map
void init_int_int_map(struct IntIntHashMap *map, int capacity) {
    map->keys = (int*)calloc(capacity, sizeof(int));
    map->values = (int*)calloc(capacity, sizeof(int));
    map->size = 0;
    map->capacity = capacity;
}

// Initialize int->float hash map
void init_int_float_map(struct IntFloatHashMap *map, int capacity) {
    map->keys = (int*)calloc(capacity, sizeof(int));
    map->values = (float*)calloc(capacity, sizeof(float));
    map->size = 0;
    map->capacity = capacity;
}

// Insert into int->int hash map
void insert_int_int(struct IntIntHashMap *map, int key, int value) {
    if (map->size < map->capacity) {
        map->keys[map->size] = key;
        map->values[map->size] = value;
        map->size++;
    }
}

// Insert into int->float hash map
void insert_int_float(struct IntFloatHashMap *map, int key, float value) {
    if (map->size < map->capacity) {
        map->keys[map->size] = key;
        map->values[map->size] = value;
        map->size++;
    }
}

int main() {
    struct IntIntHashMap student_ids;
    struct IntFloatHashMap student_scores;
    
    init_int_int_map(&student_ids, 10);
    init_int_float_map(&student_scores, 10);
    
    insert_int_int(&student_ids, 1, 12345);
    insert_int_int(&student_ids, 2, 12346);
    
    insert_int_float(&student_scores, 1, 95.5);
    insert_int_float(&student_scores, 2, 87.0);
    
    printf("Student ID map size: %d\n", student_ids.size);
    printf("Student scores map size: %d\n", student_scores.size);
    
    free(student_ids.keys);
    free(student_ids.values);
    free(student_scores.keys);
    free(student_scores.values);
    
    return 0;
}