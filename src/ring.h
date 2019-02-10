#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {
    public:
        glm::vec3 position;
        float radius;
        Ring() {}
        Ring(float x, float y, float z, float radius, float width, color_t color);
        void draw(glm::mat4 VP);

    private:
        VAO *object;
};


#endif