#include "main.h"

#ifndef STERRAIN_H
#define STERRAIN_H



class STerrain {
public:
    bool kill;
    STerrain() {}
    STerrain(int x, int y, int z, int width = 129, color_t color = COLOR_RED);
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