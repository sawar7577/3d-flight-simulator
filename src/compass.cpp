#include "main.h"
#include "compass.h"

Compass::Compass(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[10001];
    int j = 0;

    // Compass
    GLfloat *crosshar = Cuboid::CuboidArray(1.5f,0.0f,1.5f,0.0f,4.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i){
        if(i%3 == 1) {
            vertex_buffer_data[j++] = crosshar[i] - 2.0f;
        }
        else {
            vertex_buffer_data[j++] = crosshar[i];
        }
    }
    crosshar = Cuboid::CuboidArray(0.0f,1.5f,0.0f,1.5f,4.0f);

    for(int i = 0 ; i < 6*6*3 ; ++i){
        if(i%3 == 1) {
            vertex_buffer_data[j++] = crosshar[i] + 2.0f;
        }
        else {
            vertex_buffer_data[j++] = crosshar[i];
        }
    }
    
    GLfloat *color_buffer_data = new GLfloat[j];
    int i;

    for(i = 0 ; i < j/6 ; ++i) {
        color_buffer_data[3*i] = 0.1f;
        color_buffer_data[3*i+1] = 0.1f;
        color_buffer_data[3*i+2] = 0.1f;
    }
    for( ; i < j/3 ; ++i) {
        color_buffer_data[3*i] = 0.8f;
        color_buffer_data[3*i+1] = 0.8f;
        color_buffer_data[3*i+2] = 0.8f;
    }


    free(crosshar);

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color_buffer_data, GL_FILL);

}

void Compass::draw(glm::mat4 VP) {
    float top    = screen_center_y + 30 / screen_zoom;
    float bottom = screen_center_y - 30 / screen_zoom;
    float left   = screen_center_x - 30 / screen_zoom;
    float right  = screen_center_x + 30 / screen_zoom;
    VP = glm::ortho(left, right, bottom, top, 0.0f, 500.0f);

    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Compass::changeOrientation(Airplane &airp) {
    this->rotate = glm::rotate((float)(-atan2(airp.dir.x, airp.dir.z)), glm::vec3(0,0,1));
}