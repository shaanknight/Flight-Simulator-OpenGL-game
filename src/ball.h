#include "main.h"

#ifndef BALL_H
#define BALL_H


class Ball {
public:
    Ball() {}
    Ball(float x, float y, float z);
    glm::vec3 position;
    glm::mat4 local_rotation;
    float propeller_angle,speed;
    void draw(glm::mat4 VP);
    void set_position(float x, float y,float z);
    void tick();
private:
    VAO *object;
    VAO *head;
    VAO *propeller;
    VAO *fin;
};

#endif // BALL_H