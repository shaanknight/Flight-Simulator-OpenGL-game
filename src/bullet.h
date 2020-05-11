#include "main.h"

#ifndef BULLET_H
#define BULLET_H


class Bullet {
public:
    Bullet() {}
    Bullet(float x, float y,float z, color_t color,glm::vec3 dr);
    glm::vec3 position,direction;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
private:
    VAO *object;
};

#endif // BULLET_H
