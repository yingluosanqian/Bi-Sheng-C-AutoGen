/*
7_owned-struct-类型.md
定义owned struct Particle，包含position和velocity成员
*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float position;
    float velocity;
} Particle;

void update_particle(Particle* p, float dt) {
    p->position += p->velocity * dt;
}

void print_particle(const Particle* p) {
    printf("Position: %.2f, Velocity: %.2f\n", p->position, p->velocity);
}

int main() {
    Particle p = {.position = 0.0f, .velocity = 1.5f};
    
    print_particle(&p);
    update_particle(&p, 1.0f);
    print_particle(&p);
    
    return 0;
}