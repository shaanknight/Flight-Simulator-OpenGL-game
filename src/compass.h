#include "main.h"

#ifndef COMPASS_H
#define COMPASS_H


class Compass {
public:

    Compass() {}
    Compass(float x, float y, float z);
    glm::vec3 position;
    float propeller_angle;
    void draw(glm::mat4 VP);
    void setdirection(float zc,float xc);

private:
    VAO *object;
    VAO *outerring;
    VAO *innerring;
};

#endif // COMPASS_H