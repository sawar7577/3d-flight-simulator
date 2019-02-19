#include "main.h"
#include "cuboid.h"

#ifndef RING_H
#define RING_H

class Ring : public Cuboid{
    public:
        glm::vec3 position;
        float radius;
        bool kill;
        int damage;
        int points;
        Cuboid bounding;
        Ring() {}
        Ring(float x, float y, float z, float radius = 20, float width = 20, color_t color = COLOR_GREY);
        void draw(glm::mat4 VP);
        glm::mat4 rotate;

    private:
        VAO *object;
};


#endif