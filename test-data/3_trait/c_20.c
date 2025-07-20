/*
3_trait.md
为struct Json实现Encodable trait支持JSON编码
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* (*to_json)(void* self);
} Encodable;

typedef struct {
    int id;
    char* name;
    Encodable encodable;
} Json;

char* json_to_json(void* self) {
    Json* this = (Json*)self;
    char* buffer = malloc(256);
    snprintf(buffer, 256, "{\"id\":%d,\"name\":\"%s\"}", this->id, this->name);
    return buffer;
}

Json* json_new(int id, const char* name) {
    Json* obj = malloc(sizeof(Json));
    obj->id = id;
    obj->name = strdup(name);
    obj->encodable.to_json = json_to_json;
    return obj;
}

void json_free(Json* obj) {
    free(obj->name);
    free(obj);
}

int main() {
    Json* obj = json_new(1, "test");
    char* json_str = obj->encodable.to_json(obj);
    printf("%s\n", json_str);
    
    free(json_str);
    json_free(obj);
    return 0;
}
