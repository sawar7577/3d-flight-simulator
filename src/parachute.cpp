#include "main.h"
#include "parachute.h"


struct Point {
    float x, y, z;
};

std::vector <Point> returnRectangless(Point a, Point b, Point c, Point d) {
    std::vector <Point> rec;
    rec.push_back(a);
    rec.push_back(b);
    rec.push_back(c);
    rec.push_back(c);
    rec.push_back(d);
    rec.push_back(a);
    return rec;
}



Parachute::Parachute(float x, float y, float z) : Enemy(x, y, z) {
    this->position = glm::vec3(x,y,z);
    GLfloat vertex_buffer_data[100001];
    float angle = 0;
    float angle2 = 0;
    float inc = M_PI/10;
    float inc2 = M_PI/5;
    float radius = 10.0f;
    float radius2 = 02.5f;
    float width = 1.0f;
    int j = 0;
    for(int i = 0 ; i < 10 ; ++i){
        angle = 0;
        for(int k = 0 ; k < 10 ; ++k) {
            Point a1, b1, c1, d1;
            a1.x = radius*cos(angle)*cos(angle2);
            a1.z = radius*sin(angle)*cos(angle2);
            a1.y = radius*sin(angle2);

            b1.x = radius*cos(angle+inc2)*cos(angle2);
            b1.z = radius*sin(angle+inc2)*cos(angle2);
            b1.y = radius*sin(angle2);

            d1.x = radius*cos(angle)*cos(angle2+inc);
            d1.z = radius*sin(angle)*cos(angle2+inc);
            d1.y = radius*sin(angle2+inc);

            c1.x = radius*cos(angle+inc2)*cos(angle2+inc);
            c1.z = radius*sin(angle+inc2)*cos(angle2+inc);
            c1.y = radius*sin(angle2+inc);

            std::vector < Point > recs = returnRectangless(a1,b1,c1,d1);
            for(int m = 0 ; m < recs.size() ; ++m) {
                vertex_buffer_data[j++] = recs[m].x;
                vertex_buffer_data[j++] = recs[m].y;
                vertex_buffer_data[j++] = recs[m].z;
            }
            angle+=inc;
        }
        angle2+=inc;
    }
    
    GLfloat *body = Cylinder::CylinderArray(radius2, radius2, 1, radius2, 4);
    for(int i = 0 ; i < 4*4*9 ; ++i){
        if(i%3 == 1){
            vertex_buffer_data[j++] = body[i] - 10.0f;
        }
        else {
            vertex_buffer_data[j++] = body[i];
        }
    }
    free(body);
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_RED, GL_FILL);
}

void Parachute::tick(){
    this->position += glm::vec3(0,-0.1f,0);
}

void Parachute::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef

    Matrices.model = (translate * this->rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

glm::vec3 Parachute::locationScreen(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    std::cout << this->position.y << std::endl;
    return glm::vec3(VP * glm::vec4(this->position,1));
}