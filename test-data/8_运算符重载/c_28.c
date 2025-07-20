/*
8_运算符重载.md
重载>运算符比较两个版本号
*/
#include <stdio.h>

struct Version { int major; int minor; };

int compare_versions(struct Version v1, struct Version v2) {
    if (v1.major > v2.major) return 1;
    if (v1.major == v2.major && v1.minor > v2.minor) return 1;
    return 0;
}

int main() {
    struct Version v1 = {1, 2};
    struct Version v2 = {1, 1};
    printf("%d\n", compare_versions(v1, v2));
    return 0;
}