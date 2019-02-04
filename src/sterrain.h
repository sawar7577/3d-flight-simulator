#include "main.h"

#ifndef STERRAIN_H
#define STERRAIN_H



class STerrain {
public:
    STerrain() {}
    STerrain(int x, int y, int width, color_t color);
    glm::vec3 position;
    float rotation;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif 