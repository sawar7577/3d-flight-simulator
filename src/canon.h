#include "main.h"
#include "enemy.h"

#ifndef CANON_H
#define CANON_H

class Canon :  public Enemy {
    public:
        glm::vec3 position;
        float radius;
        Canon() {}
        Canon(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);


    private:
        VAO *object;
};


#endif