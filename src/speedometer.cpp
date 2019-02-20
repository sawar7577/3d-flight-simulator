#include "main.h"
#include "speedometer.h"

Speedometer::Speedometer(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[100001];
    int j = 0;
    float angle = 0.0f;
    float inc = M_PI/20;
    float radius = 10.0f;
    float radius2 = 9.0f;
    for(int i = 0 ; i < 20 ; ++i) {
        Point a,b,c,d;
        a.x = radius*cos(angle);
        a.y = radius*sin(angle);
        a.z = 0.0f;

        b.x = radius*cos(angle + inc);
        b.y = radius*sin(angle + inc);
        b.z = 0.0f;

        c.x = radius2*cos(angle + inc);
        c.y = radius2*sin(angle + inc);
        c.z = 0.0f;

        d.x = radius2*cos(angle);
        d.y = radius2*sin(angle);
        d.z = 0.0f;

        std::vector <Point> rec = returnRectangles(a,b,c,d);
        for(int k = 0 ; k < rec.size() ; ++k) {
            vertex_buffer_data[j++] = rec[k].x;
            vertex_buffer_data[j++] = rec[k].y;
            vertex_buffer_data[j++] = rec[k].z;
        }
        angle += inc;
    }
    
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_BLACK, GL_FILL);

    j = 0;
    GLfloat *crosshar = CuboidArray(0.0f,2.0f,0.0f,2.0f,8.0f);
    for(int i = 0 ; i < 6*6*3 ; ++i) {
        if(i%3 == 1) {
            vertex_buffer_data[j++] = crosshar[i] + 4.0f;
        }
        else {
            vertex_buffer_data[j++] = crosshar[i];
        }
    }
    free(crosshar);
    this->meter = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_BLACK, GL_FILL);

}

void Speedometer::draw(glm::mat4 VP) {
    float top    = screen_center_y + 30 / screen_zoom;
    float bottom = screen_center_y - 30 / screen_zoom;
    float left   = screen_center_x - 30 / screen_zoom;
    float right  = screen_center_x + 30 / screen_zoom;
    VP = glm::ortho(left, right, bottom, top, 0.0f, 500.0f);

    Matrices.model = glm::mat4(1.0f);
    
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    
    Matrices.model = (translate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);

    Matrices.model = (translate * this->rotate);
    MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->meter);
}

void Speedometer::changeSpeed(Airplane &airp) {
    float speed = airp.speed;
    this->rotate = glm::rotate((float)(M_PI/2 - M_PI*( (speed/10.0f))), glm::vec3(0,0,1));
}