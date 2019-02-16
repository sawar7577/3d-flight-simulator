#include "ring.h"
#include "main.h"


Ring::Ring(float x, float y, float z, float radius, float width, color_t color) {
    this->position = glm::vec3(x,y,z);
    this->radius = radius;

    float angle = 0;
    float inc = 2*M_PI/30;
    GLfloat vertex_buffer_data[1000001];
    int j = 0;
    for(int i = 0 ; i < 50 ; ++i) {
        Point a1, b1, c1, d1;
        a1.x = radius*cos(angle);
        a1.y = radius*sin(angle);
        a1.z = width/2;

        b1.x = radius*cos(angle+inc);
        b1.y = radius*sin(angle+inc);
        b1.z = width/2;

        d1.x = 0.9*radius*cos(angle);
        d1.y = 0.9*radius*sin(angle);
        d1.z = width/2;

        c1.x = 0.9*radius*cos(angle+inc);
        c1.y = 0.9*radius*sin(angle+inc);
        c1.z = width/2;

        Point a2, b2, c2, d2;
        a2.x = radius*cos(angle);
        a2.y = radius*sin(angle);
        a2.z = -width/2;

        b2.x = radius*cos(angle+inc);
        b2.y = radius*sin(angle+inc);
        b2.z = -width/2;

        d2.x = 0.9*radius*cos(angle);
        d2.y = 0.9*radius*sin(angle);
        d2.z = -width/2;

        c2.x = 0.9*radius*cos(angle+inc);
        c2.y = 0.9*radius*sin(angle+inc);
        c2.z = -width/2;

        std::vector <Point> recs = returnRectangles(a1, b1, c1, d1);

        for(int k = 0 ; k < recs.size() ; ++k) {
            vertex_buffer_data[j++] = recs[k].x;
            vertex_buffer_data[j++] = recs[k].y;
            vertex_buffer_data[j++] = recs[k].z;
        }

        recs.clear();
        recs = returnRectangles(a2, b2, c2, d2);

        for(int k = 0 ; k < recs.size() ; ++k) {
            vertex_buffer_data[j++] = recs[k].x;
            vertex_buffer_data[j++] = recs[k].y;
            vertex_buffer_data[j++] = recs[k].z;
        }

        recs.clear();

        recs = returnRectangles(a1, b1, b2, a2);
        
        for(int k = 0 ; k < recs.size() ; ++k) {
            vertex_buffer_data[j++] = recs[k].x;
            vertex_buffer_data[j++] = recs[k].y;
            vertex_buffer_data[j++] = recs[k].z;
        }

        recs.clear();

        recs = returnRectangles(d1, c1, c2, d2);

        for(int k = 0 ; k < recs.size() ; ++k) {
            vertex_buffer_data[j++] = recs[k].x;
            vertex_buffer_data[j++] = recs[k].y;
            vertex_buffer_data[j++] = recs[k].z;
        }

        recs.clear();
        angle += inc;
    }

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);

}

void Ring::draw(glm::mat4 VP){
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    Matrices.model = (translate);
    glm::mat4 MVP = VP * Matrices.model;
    
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}



