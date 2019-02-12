#include "main.h"
#include "enemy.h"

Enemy::Enemy(float x, float y, float z){
    this->position = glm::vec3(x,y,z);
    this->rotate = glm::mat4(1.0f);
}

void Enemy::tick(){
    this->position += glm::vec3(0,-1,+1);
}

void Enemy::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}