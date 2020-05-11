#include "main.h"

#ifndef ALTITUDE_H
#define ALTITUDE_H


class Altitude {
public:

    Altitude() {}
    Altitude(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);

private:
    VAO *object;
};

#endif // ALTITUDE_H