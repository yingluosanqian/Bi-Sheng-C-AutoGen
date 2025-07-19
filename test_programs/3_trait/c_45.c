/*
3_trait.md
FileHandler trait为File结构体实现open和close方法
*/
#include <stdio.h>
#include <stdlib.h>

struct File {
    FILE* fp;
};

int File_open(struct File* this, const char* filename, const char* mode) {
    this->fp = fopen(filename, mode);
    return this->fp != NULL;
}

void File_close(struct File* this) {
    if (this->fp) {
        fclose(this->fp);
        this->fp = NULL;
    }
}

int main() {
    struct File file;
    if (File_open(&file, "test.txt", "w")) {
        fprintf(file.fp, "Hello World");
        File_close(&file);
    }
    return 0;
}