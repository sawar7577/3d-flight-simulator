#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "airplane.h"

#ifndef ALTIMETER_H
#define ALTIMETER_H

class Altimeter : public Cylinder, public Cuboid{
    public:
        glm::vec3 position;
        float radius;
        Altimeter() {}
        Altimeter(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);
        void changeHeight(Airplane &airp);


    private:
        VAO *object;
};


#endif