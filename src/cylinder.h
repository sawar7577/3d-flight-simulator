#include "main.h"

#ifndef CYLINDER_H
#define CYLINDER_H


class Cylinder {
public:
    Cylinder() {}
    Cylinder(float x, float y, float radius1, float radius2, float ecc, float height, int vertices, color_t color);
    GLfloat * CylinderArray(float radius1, float radius2, float ecc, float height, int vertices);
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