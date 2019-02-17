#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "parachute.h"

#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H


class Enemyplane : public Cylinder, public Cuboid{
public:
    float pitch, yaw, roll;
    bool pitch_v, yaw_v, roll_v;
    float fvalue;
    bool kill;
    int arg;
    Cuboid bounding;
    Enemyplane() {}
    Enemyplane(float x, float y, float z, float radius1 = 1.0f, float radius2 = 1.0f, float ecc = 1.0f, float height = 5.0f, int vertices = 30, color_t color = COLOR_GREEN);
    glm::vec3 position;
    glm::vec3 dir;
    glm::vec3 up;
    glm::vec3 velocity;
    glm::mat4 rotate;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    glm::vec3 locationScreen(glm::mat4 VP);

    void tick();
    double speed;
private:
    VAO *object;
};

#endif 