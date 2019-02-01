#include "main.h"
#include "cylinder.h"

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane : public Cylinder{
public:
    Airplane() {}
    Airplane(float x, float y, float radius1, float radius2, float ecc, float height, int vertices, color_t color);
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