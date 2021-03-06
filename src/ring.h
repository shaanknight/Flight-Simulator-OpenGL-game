#include "main.h"

#ifndef RING_H
#define RING_H


class Ring {
public:
    Ring() {}
    Ring(float x, float y, float z);
    glm::vec3 position;
    float propeller_angle;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
private:
    VAO *object;
    VAO *arrow;
};

#endif // RING_H