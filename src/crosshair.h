#include "main.h"
#include "cylinder.h"
#include "cuboid.h"

#ifndef CROSSHAIR_H
#define CROSSHAIR_H

class Crosshair : public Cylinder, public Cuboid{
    public:
        glm::vec3 position;
        float radius;
        Crosshair() {}
        Crosshair(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);
        void changeColor(bool flag);


    private:
        VAO *object;
};


#endif