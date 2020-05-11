#include "main.h"

#ifndef SEA_H
#define SEA_H


class Sea {
public:

    Sea() {}
    Sea(float x, float y, float z);
    glm::vec3 position;
    void draw(glm::mat4 VP);

private:
    VAO *object;
};

#endif // SEA_H