#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "parachute.h"
#include "enemyplane.h"
#include "missile.h"
#include "bomb.h"
#include <typeinfo>

#ifndef AIRPLANE_H
#define AIRPLANE_H


class Airplane : public Cylinder, public Cuboid{
public:
    float pitch, yaw, roll;
    float fvalue;
    float speed;
    int counter;
    bool barrel_roll;
    bool loop_the_loop;
    clock_t cooldown;
    Parachute *target;
    Enemyplane *etarget;
    Cuboid bounding;
    Airplane() {}
    Airplane(float x, float y, float radius1, float radius2, float ecc, float height, int vertices, color_t color);
    glm::vec3 position;
    glm::vec3 dir;
    glm::vec3 up;
    glm::vec3 velocity;
    glm::mat4 rotate;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick(GLFWwindow *window);
    void setTarget(void *tar, int arg) {
        if(arg == 0) {
            this->target = (Parachute *)tar;
        }
        if(arg == 1) {
            this->etarget = (Enemyplane *)tar;
        }
    }
private:
    VAO *object;
};


#endif 