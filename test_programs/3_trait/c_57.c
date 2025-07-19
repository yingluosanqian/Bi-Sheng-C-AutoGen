/*
3_trait.md
泛型trait Parser<T>为JsonParser结构体实现parse和validate方法
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char* data;
} JsonParser;

int JsonParser_parse(JsonParser* this, char* output) {
    sprintf(output, "Parsed: %s", this->data);
    return 1;
}

int JsonParser_validate(JsonParser* this) {
    return this->data != NULL;
}

int main() {
    JsonParser parser = {"{\"key\":\"value\"}"};
    char output[100];
    
    if (JsonParser_validate(&parser)) {
        JsonParser_parse(&parser, output);
        printf("{\"result\":\"%s\", \"valid\":true}", output);
    } else {
        printf("{\"result\":\"\", \"valid\":false}");
    }
    
    return 0;
}