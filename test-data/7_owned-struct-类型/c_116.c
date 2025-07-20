/*
7_owned-struct-类型.md
定义owned struct PhysicsBody，包含position和velocity成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float position;
    float velocity;
} PhysicsBody;

void updatePhysicsBody(PhysicsBody *body, float deltaTime) {
    body->position += body->velocity * deltaTime;
}

void printPhysicsBody(const PhysicsBody *body) {
    printf("Position: %.2f, Velocity: %.2f\n", body->position, body->velocity);
}

int main() {
    PhysicsBody body = {.position = 0.0f, .velocity = 2.5f};
    
    printPhysicsBody(&body);
    updatePhysicsBody(&body, 1.0f);
    printPhysicsBody(&body);
    
    return 0;
}