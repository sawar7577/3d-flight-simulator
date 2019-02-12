#include "main.h"
#include "cylinder.h"
#include "enemy.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile : public Cylinder {
    public:
        glm::vec3 position;
        float radius;
        Missile() {}
        Missile(float x, float y, float z, float radius, float length, int vertices, color_t color);
        void draw(glm::mat4 VP);
        void tick();
        Enemy *follow;
        glm::mat4 rotate;

    private:
        VAO *object;
};


#endif