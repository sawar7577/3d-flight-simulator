#include "main.h"
#include "cylinder.h"
#include "cuboid.h"

#ifndef FUEL_H
#define FUEL_H

class Fuel : public Cylinder, public Cuboid{
    public:
        glm::vec3 position;
        float radius;

        Fuel() {}
        Fuel(float x, float y, float z);
        glm::mat4 rotate;
        void tick(float percent);
        void draw(glm::mat4 VP);


    private:
        VAO *object;
};


#endif