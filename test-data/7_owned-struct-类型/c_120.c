/*
7_owned-struct-类型.md
定义owned struct RigidBody，包含mass和velocity成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    double mass;
    double velocity;
} RigidBody;

void print_rigid_body(const RigidBody* body) {
    printf("Mass: %.2f, Velocity: %.2f\n", body->mass, body->velocity);
}

int main() {
    RigidBody body = {.mass = 10.5, .velocity = 3.2};
    print_rigid_body(&body);
    return 0;
}