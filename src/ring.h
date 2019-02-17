#include "main.h"

#ifndef RING_H
#define RING_H

class Ring {
    public:
        glm::vec3 position;
        float radius;
        bool kill;
        Ring() {}
        Ring(float x, float y, float z, float radius = 20, float width = 20, color_t color = COLOR_BLACK);
        void draw(glm::mat4 VP);

    private:
        VAO *object;
};


#endif