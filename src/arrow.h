#include "main.h"
#include "cuboid.h"

#ifndef ARROW_H
#define ARROW_H

class Arrow :  public Cuboid {
    public:
        glm::vec3 position;
        float radius;
        glm::vec3 dir;
        Arrow() {}
        Arrow(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);


    private:
        VAO *object;
};

#endif