#include "main.h"
#include "cylinder.h"
#include "enemy.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H

class Parachute : public Cylinder, public Enemy {
    public:
        glm::vec3 position;
        float radius;
        Parachute() {}
        Parachute(float x, float y, float z);
        glm::mat4 rotate;

    private:
        VAO *object;
};


#endif