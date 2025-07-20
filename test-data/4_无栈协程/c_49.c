/*
4_无栈协程.md
async函数处理地理位置获取模拟
*/
#include <stdio.h>
#include <stdlib.h>

struct Location {
    double latitude;
    double longitude;
};

struct Location get_location_sync() {
    struct Location loc;
    loc.latitude = 37.7749;
    loc.longitude = -122.4194;
    return loc;
}

int main() {
    struct Location loc = get_location_sync();
    printf("{\"latitude\":%f,\"longitude\":%f}", loc.latitude, loc.longitude);
    return 0;
}