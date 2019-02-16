#include "main.h"
#include "cylinder.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public Cylinder {
    public:
        bool kill;
        glm::vec3 position;
        glm::vec3 dir;
        float radius;
        Bullet() {}
        Bullet(float x, float y, float z, float radius, float length, int vertices, glm::vec3 d, color_t color);
        void draw(glm::mat4 VP);
        void tick();
        glm::mat4 rotate;

    private:
        VAO *object;
};

// list <Bullet> bs;
// list <Bullet> bs;

#endif