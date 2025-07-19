/*
7_owned-struct-类型.md
创建owned struct PhysicsBody实例并初始化position和velocity
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x;
    float y;
} Vector2;

typedef struct {
    Vector2 position;
    Vector2 velocity;
} PhysicsBody;

int main() {
    PhysicsBody body = {
        .position = {.x = 10.5f, .y = 20.3f},
        .velocity = {.x = 1.2f, .y = -0.5f}
    };
    
    printf("{\"position\":{\"x\":%.1f,\"y\":%.1f},\"velocity\":{\"x\":%.1f,\"y\":%.1f}}\n",
           body.position.x, body.position.y,
           body.velocity.x, body.velocity.y);
    
    return 0;
}