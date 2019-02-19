#include "main.h"
#include "cylinder.h"
#include "cuboid.h"
#include "airplane.h"

#ifndef SCORE_H
#define SCORE_H

class Score : public Cylinder, public Cuboid{
    public:
        glm::vec3 position;
        float radius;
        Score() {}
        Score(float x, float y, float z);
        glm::mat4 rotate;
        void tick();
        void draw(glm::mat4 VP);
        void changeScore(int numb);
        GLfloat *giveNumber(std::string hash);
        int giveCount(std::string hash);


    private:
        VAO *object;
};


#endif