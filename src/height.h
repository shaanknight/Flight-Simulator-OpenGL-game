#include "main.h"

#ifndef HEIGHT_H
#define HEIGHT_H


class Height {
public:

    Height() {}
    Height(float x, float y, float z,color_t color);
    glm::vec3 position;
    void draw(glm::mat4 VP);

private:
    VAO *object;
};

#endif // ALTITUDE_H