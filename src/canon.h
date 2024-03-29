#include "main.h"
#include "enemy.h"
#include "airplane.h"
#include "bullet.h"


#ifndef CANON_H
#define CANON_H

class Canon :  public Enemy {
    public:
        glm::vec3 position;
        float radius;
        glm::vec3 dir;
        int damage;
        int points;
        bool kill;
        Cuboid bounding;
        Canon() {}
        Canon(float x, float y, float z, Airplane *target);
        glm::mat4 rotate;
        void tick();
        Airplane *target;
        void draw(glm::mat4 VP);


    private:
        VAO *object;
};



#endif
extern std::list <Bullet> bs;