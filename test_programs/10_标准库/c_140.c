/*
10_标准库.md
使用Vec实现一个带索引的日志收集器
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char** entries;
    size_t capacity;
    size_t length;
} Logger;

void log_message(Logger* logger, const char* msg) {
    if (logger->length >= logger->capacity) {
        logger->capacity *= 2;
        logger->entries = realloc(logger->entries, logger->capacity * sizeof(char*));
    }
    logger->entries[logger->length] = strdup(msg);
    logger->length++;
}

void print_log(const Logger* logger) {
    for (size_t i = 0; i < logger->length; i++) {
        printf("[%zu] %s\n", i, logger->entries[i]);
    }
}

void free_logger(Logger* logger) {
    for (size_t i = 0; i < logger->length; i++) {
        free(logger->entries[i]);
    }
    free(logger->entries);
}

int main() {
    Logger logger = {
        .entries = malloc(2 * sizeof(char*)),
        .capacity = 2,
        .length = 0
    };

    log_message(&logger, "System started");
    log_message(&logger, "Initialization complete");
    print_log(&logger);
    free_logger(&logger);
    return 0;
}