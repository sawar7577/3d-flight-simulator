#include "arrow.h"

Arrow::Arrow(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[100000];

    int j = 0;

    // Crosshair
    GLfloat *crosshar = Cuboid::CuboidArray(10.5f,10.5f,10.5f,10.5f,80.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i){
        vertex_buffer_data[j++] = crosshar[i];
    }
    crosshar = Cuboid::CuboidArray(20.0f,0.0f,20.0f,0.0f,20.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i){
        if(i%3 == 1) {
            vertex_buffer_data[j++] = crosshar[i] - 50.0f;
        }
        else {
            vertex_buffer_data[j++] = crosshar[i];
        }
    }
    free(crosshar);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_GREEN, GL_FILL);

}

void Arrow::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}