#include "main.h"
#include "enemy.h"
#include "cuboid.h"

#ifndef PARACHUTE_H
#define PARACHUTE_H

class Parachute :  public Enemy {
    public:
        int arg;
        bool kill;
        glm::vec3 position;
        float radius;
        Cuboid bounding;
        Parachute() {}
        Parachute(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);
        glm::vec3 locationScreen(glm::mat4 VP);



    private:
        VAO *object;
};


#endif