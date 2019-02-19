#include "main.h"
#include "cuboid.h"

#ifndef VOLCANO_H
#define VOLCANO_H

class Volcano : public Cuboid{
    public:
        glm::vec3 position;
        float rotation;
        float radius;
        bool kill;
        int damage;
        int points;
        Cuboid bounding;
        glm::vec3 dir;
        Volcano() {}
        Volcano(int x, int y, int z, int width = 65);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);


    private:
        VAO *object;
};



#endif