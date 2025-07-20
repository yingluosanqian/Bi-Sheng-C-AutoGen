/*
3_trait.md
为struct Config实现Loadable trait加载配置
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// In standard C, we simulate traits using function pointers
struct Config {
    char *filename;
    int value;
    
    // Function pointers to simulate trait methods
    int (*load)(struct Config *self);
    void (*print)(struct Config *self);
};

int config_load(struct Config *self) {
    FILE *file = fopen(self->filename, "r");
    if (!file) return 0;
    
    char buffer[256];
    if (fgets(buffer, sizeof(buffer), file)) {
        self->value = atoi(buffer);
    }
    
    fclose(file);
    return 1;
}

void config_print(struct Config *self) {
    printf("Config '%s' loaded with value: %d\n", self->filename, self->value);
}

struct Config create_config(const char *filename) {
    struct Config cfg = {
        .filename = strdup(filename),
        .value = 0,
        .load = config_load,
        .print = config_print
    };
    return cfg;
}

void destroy_config(struct Config *cfg) {
    free(cfg->filename);
}

int main() {
    struct Config cfg = create_config("config.txt");
    
    if (cfg.load(&cfg)) {
        cfg.print(&cfg);
    } else {
        printf("Failed to load config\n");
    }
    
    destroy_config(&cfg);
    return 0;
}
