#include "main.h"

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H


class Speedometer {
public:

    Speedometer() {}
    Speedometer(float x, float y, float z);
    glm::vec3 position;
    float propeller_angle;
    void draw(glm::mat4 VP);
    void setdirection(float xc);

private:
    VAO *object;
    VAO *outerring;
    VAO *innerring;
};

#endif // SPEEDOMETER_H