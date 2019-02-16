#include "fuelup.h"

Fuelup::Fuelup(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    this->kill = false;
    GLfloat vertex_buffer_data[100000];

    int j = 0;

    // Crosshair
    GLfloat *crosshar = Cuboid::CuboidArray(11.5f,11.5f,4.5f,4.5f,8.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i){
        vertex_buffer_data[j++] = crosshar[i];
    }
    GLfloat *op =CylinderArray(1.0f,1.0f,1.0f,3.0f,20);
    for(int i = 0 ; i < 4*9*20 ; ++i) {
        if(i%3 == 0) {
            vertex_buffer_data[j++] = op[i] + 3.0f;
        }
        else if(i%3 == 1) {
            vertex_buffer_data[j++] = op[i] + 4.0f;
        }
        else{
            vertex_buffer_data[j++] = op[i];
        }
    }

    free(op);
    free(crosshar);
    this->bounding = Cuboid(x,y,z,10, 10, 10, 10, 10, COLOR_RED);

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_GREEN, GL_FILL);

}

void Fuelup::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

// void Fuelup::action(air)