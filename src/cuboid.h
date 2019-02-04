#include "main.h"

#ifndef CUBOID_H
#define CUBOID_H


class Cuboid {
public:
    Cuboid() {}
    Cuboid(float x, float y, float length1 , float length2, float breadth1, float breadth2, float height, color_t color);
    GLfloat * CuboidArray(float length1, float length2, float breadth1, float breadth2, float height);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif 