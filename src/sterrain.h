#include "main.h"
#include "cuboid.h"

#ifndef STERRAIN_H
#define STERRAIN_H



class STerrain : public Cuboid {
public:
    bool kill;
    Cuboid bounding;
    STerrain() {}
    STerrain(int x, int y, int z, int width = 129, color_t color = COLOR_RED);
    glm::vec3 position;
    float rotation;
    glm::mat4 rotate;
    void draw(glm::mat4 VP);
    void set_position(float x, float y);
    void tick();
    double speed;
private:
    VAO *object;
};

#endif 