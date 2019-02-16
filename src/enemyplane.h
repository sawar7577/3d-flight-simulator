#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "parachute.h"

#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H


class Enemyplane : public Cylinder, public Cuboid{
public:
    float pitch, yaw, roll;
    float fvalue;
    Parachute *target;
    Cuboid bounding;
    Enemyplane() {}
    Enemyplane(float x, float y, float radius1, float radius2, float ecc, float height, int vertices, color_t color);
    glm::vec3 position;
    glm::vec3 dir;
    glm::vec3 up;
    glm::vec3 velocity;
    glm::mat4 rotate;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif 