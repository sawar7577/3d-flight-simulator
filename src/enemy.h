#include "main.h"
#include "cylinder.h"

#ifndef ENEMY_H
#define ENEMY_H

class Enemy : public Cylinder {
    public:
        glm::vec3 position;
        float radius;
        Enemy() {}
        Enemy(float x, float y, float z);
        void draw(glm::mat4 VP);
        void tick();
        glm::mat4 rotate;

    private:
        VAO *object;
};


#endif