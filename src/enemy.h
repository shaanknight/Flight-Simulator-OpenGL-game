#include "main.h"

#ifndef ENEMY_H
#define ENEMY_H


class Enemy {
public:

    Enemy() {}
    Enemy(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);

private:
    VAO *lcube;
    VAO *ucube;
    VAO *carpet;
    VAO *cylinder;
};

#endif // ENEMY_H