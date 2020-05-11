#include "main.h"

#ifndef POWER_H
#define POWER_H


class Power {
public:
    Power() {}
    Power(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
private:
    VAO *inner_ring;
    VAO *outer_ring;
    VAO *cross;
};

#endif // POWER_H