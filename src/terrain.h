#include "main.h"

#ifndef TERRAIN_H
#define TERRAIN_H


class Terrain {
public:
    Terrain() {}
    Terrain(int x, int y, int width, int height, color_t color);
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