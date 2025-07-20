/*
1_泛型.md
常量泛型实现固定大小的哈希表，桶数量可配置
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKET_COUNT_5 5
#define BUCKET_COUNT_10 10

struct HashNode {
    int key;
    int value;
    struct HashNode* next;
};

struct HashTable5 {
    struct HashNode* buckets[BUCKET_COUNT_5];
};

struct HashTable10 {
    struct HashNode* buckets[BUCKET_COUNT_10];
};

int hash5(int key) {
    return key % BUCKET_COUNT_5;
}

int hash10(int key) {
    return key % BUCKET_COUNT_10;
}

void insert5(struct HashTable5* table, int key, int value) {
    int index = hash5(key);
    struct HashNode* node = malloc(sizeof(struct HashNode));
    node->key = key;
    node->value = value;
    node->next = table->buckets[index];
    table->buckets[index] = node;
}

void insert10(struct HashTable10* table, int key, int value) {
    int index = hash10(key);
    struct HashNode* node = malloc(sizeof(struct HashNode));
    node->key = key;
    node->value = value;
    node->next = table->buckets[index];
    table->buckets[index] = node;
}

int get5(struct HashTable5* table, int key) {
    int index = hash5(key);
    struct HashNode* node = table->buckets[index];
    while (node) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

int get10(struct HashTable10* table, int key) {
    int index = hash10(key);
    struct HashNode* node = table->buckets[index];
    while (node) {
        if (node->key == key) {
            return node->value;
        }
        node = node->next;
    }
    return -1;
}

int main() {
    struct HashTable5 table5 = {0};
    struct HashTable10 table10 = {0};
    
    insert5(&table5, 1, 100);
    insert5(&table5, 6, 200);
    
    insert10(&table10, 1, 100);
    insert10(&table10, 11, 300);
    
    printf("HashTable5 - Key 1: %d\n", get5(&table5, 1));
    printf("HashTable5 - Key 6: %d\n", get5(&table5, 6));
    printf("HashTable10 - Key 1: %d\n", get10(&table10, 1));
    printf("HashTable10 - Key 11: %d\n", get10(&table10, 11));
    
    return 0;
}