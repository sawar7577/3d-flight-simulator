#include "main.h"
#include "cuboid.h"
#include "cylinder.h"

#ifndef FUELUP_H
#define FUELUP_H

class Fuelup :  public Cuboid, public Cylinder {
    public:
        glm::vec3 position;
        float radius;
        bool kill;
        glm::vec3 dir;
        Cuboid bounding;
        int damage;
        int points;
        Fuelup() {}
        Fuelup(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);


    private:
        VAO *object;
};

#endif