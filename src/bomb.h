#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "enemy.h"
#include "parachute.h"
#include "enemyplane.h"

#ifndef BOMB_H
#define BOMB_H

class Bomb : public Cylinder, public Cuboid {
    public:
        glm::vec3 position;
        glm::vec3 dir;
        float radius;
        bool kill;
        int damage;
        int points;
        Cuboid bounding;
        Bomb() {}
        Bomb(float x, float y, float z, float radius, float length, int vertices, glm::vec3 d, color_t color);
        void draw(glm::mat4 VP);
        void tick();
        glm::mat4 rotate;

    private:
        VAO *object;
};

extern std::list <Bomb> bms;

#endif