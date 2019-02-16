#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "crosshair.h"
#include "fuel.h"
#include "airplane.h"
#include "compass.h"
#include "altimeter.h"

#ifndef DASHBOARD_H
#define DASHBOARD_H

class Dashboard : public Cylinder, public Cuboid{
    public:
        glm::vec3 position;
        float radius;
        Crosshair cross;
        Fuel f;
        Compass cp;
        Altimeter ap;
        Dashboard() {}
        Dashboard(float x, float y, float z);
        glm::mat4 rotate;
        void tick(Airplane &air);
        void draw(glm::mat4 VP);
        void setCrosshair(bool flag);



    private:
        VAO *object;
};


#endif