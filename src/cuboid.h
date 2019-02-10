#include "main.h"

#ifndef CUBOID_H
#define CUBOID_H


class Cuboid {
public:
    float length1, length2, breadth1, breadth2, height;
    Cuboid() {}
    Cuboid(float x, float y, float z, float length1 , float length2, float breadth1, float breadth2, float height, color_t color);
    GLfloat * CuboidArray(float length1, float length2, float breadth1, float breadth2, float height);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
// private:
    VAO *object;
};

#endif 