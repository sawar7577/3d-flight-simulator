#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "airplane.h"

#ifndef COMPASS_H
#define COMPASS_H

class Compass : public Cylinder, public Cuboid{
    public:
        glm::vec3 position;
        float radius;
        Compass() {}
        Compass(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);
        void changeOrientation(Airplane &airp);


    private:
        VAO *object;
};


#endif