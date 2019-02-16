#include "main.h"

#ifndef VOLCANO_H
#define VOLCANO_H

class Volcano {
    public:
        glm::vec3 position;
        float rotation;
        float radius;
        glm::vec3 dir;
        Volcano() {}
        Volcano(int x, int y, int width);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);


    private:
        VAO *object;
};



#endif