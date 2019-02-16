#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "airplane.h"

#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

class Speedometer : public Cylinder, public Cuboid{
    public:
        glm::vec3 position;
        glm::vec3 meterposition;
        float radius;
        Speedometer() {}
        Speedometer(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);
        void changeSpeed(Airplane &airp);


    private:
        VAO *object;
        VAO *meter;
};


#endif