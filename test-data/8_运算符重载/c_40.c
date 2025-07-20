/*
8_运算符重载.md
重载==运算符比较两个GPS坐标
*/
#include <stdio.h>

struct GPS {
    double lat;
    double lon;
};

int gps_equal(struct GPS g1, struct GPS g2) {
    return (g1.lat == g2.lat) && (g1.lon == g2.lon);
}

int main() {
    struct GPS g1 = {40.7128, -74.0060};
    struct GPS g2 = {40.7128, -74.0060};
    
    if (gps_equal(g1, g2)) {
        printf("The GPS coordinates are equal.\n");
    } else {
        printf("The GPS coordinates are not equal.\n");
    }
    
    return 0;
}