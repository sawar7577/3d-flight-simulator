#include "main.h"
#include "cylinder.h"
#include "enemy.h"
#include "parachute.h"
#include "enemyplane.h"
#include "cuboid.h"

#ifndef MISSILE_H
#define MISSILE_H

class Missile : public Cylinder {
    public:
        glm::vec3 position;
        glm::vec3 dir;
        float radius;
        
        int damage;
        int points;
        bool kill;
        Cuboid bounding;
        Missile() {}
        Missile(float x, float y, float z, float radius, float length, int vertices, glm::vec3 d, color_t color);
        void draw(glm::mat4 VP);
        void tick();
        // template <typename Type> void setPointer(Type *track);
        Parachute *follow;
        Enemyplane *efollow;
        glm::mat4 rotate;

    private:
        VAO *object;
};

extern std::list <Missile> ms;

#endif