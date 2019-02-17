#include "bomb.h"
#include "main.h"

Bomb::Bomb(float x, float y, float z, float radius, float length, int vertices, glm::vec3 d, color_t color) {

    this->rotate = glm::mat4(1.0f);
    this->position = glm::vec3(x, y, z);
    this->kill = false;
    this->dir = d;
    GLfloat vertex_buffer_data[100000];
    int i = 0;
    int j = 0;
    GLfloat *body = Cylinder::CylinderArray(radius, 0.8*radius, 1, 0.7*length, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        vertex_buffer_data[j] = body[i];
    }
    free(body);

    GLfloat *front = Cylinder::CylinderArray(0.25f, radius, 1, 0.15*length, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        if(i%3 == 1)
            vertex_buffer_data[j] = front[i] + (0.7*length + 0.15*length)/2;
        else
            vertex_buffer_data[j] = front[i];
    }
    free(front);

    GLfloat *back = Cylinder::CylinderArray(0.8*radius, radius, 1, 0.15*length, 25);
    for(i = 0 ; i < 36*25 ; ++i, ++j) {
        if(i%3 == 1)
            vertex_buffer_data[j] = back[i] - (0.7*length + 0.15*length)/2;
        else
            vertex_buffer_data[j] = back[i];
    }
    free(back);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}


void Bomb::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Bomb::tick(){
    this->position += glm::vec3(0,-1.0f,0);
}




