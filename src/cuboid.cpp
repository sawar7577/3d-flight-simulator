#include "cuboid.h"
#include "main.h"

Cuboid::Cuboid(float x, float y, float z, float length1 , float length2, float breadth1, float breadth2, float height, color_t color) {
    this->length1 = length1;
    this->length2 = length2;
    this->breadth1 = breadth1;
    this->breadth2 = breadth2;
    this->height = height;

    this->position = glm::vec3(x, y, z);
    this->rotation = 0;
    
    speed = 1;
    float angle = 0;
    GLfloat vertex_buffer_data[100000];
    
    int j = 0;
    int i = 0;
    GLfloat *body = CuboidArray(length1, length2, breadth1, breadth2, height);
    for(i = 0 ; i < 6*6*3 ; ++i,++j){
        vertex_buffer_data[i] = body[i];
    }
    free(body);

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color, GL_FILL);
}

GLfloat * Cuboid::CuboidArray(float length1, float length2, float breadth1, float breadth2, float height) {
    
    GLfloat * vertex_buffer_data = (GLfloat *)malloc(sizeof(GLfloat) * 6*6*3);
   GLfloat front[] = {
        -length1/2, +height/2, -breadth1/2,
        -length1/2, +height/2, breadth1/2,
        length1/2, +height/2, breadth1/2,
        length1/2, +height/2, -breadth1/2,
    };
    GLfloat back[] = {
        -length2/2, -height/2, -breadth2/2,
        -length2/2, -height/2, breadth2/2,
        length2/2, -height/2, breadth2/2,
        length2/2, -height/2, -breadth2/2,
    };

    int i,j;
    j = 0;
    for(i = 0 ; i < 4; ++i)
    {
        vertex_buffer_data[j++] = front[(3*i)%12];
        vertex_buffer_data[j++] = front[(3*i+1)%12];
        vertex_buffer_data[j++] = front[(3*i+2)%12];

        vertex_buffer_data[j++] = front[(3*(i+1))%12];
        vertex_buffer_data[j++] = front[(3*(i+1)+1)%12];
        vertex_buffer_data[j++] = front[(3*(i+1)+2)%12];


        vertex_buffer_data[j++] = back[(3*(i))%12];
        vertex_buffer_data[j++] = back[(3*(i)+1)%12];
        vertex_buffer_data[j++] = back[(3*(i)+2)%12];


        vertex_buffer_data[j++] = back[(3*i)%12];
        vertex_buffer_data[j++] = back[(3*i+1)%12];
        vertex_buffer_data[j++] = back[(3*i+2)%12];

        vertex_buffer_data[j++] = back[(3*(i+1))%12];
        vertex_buffer_data[j++] = back[(3*(i+1)+1)%12];
        vertex_buffer_data[j++] = back[(3*(i+1)+2)%12];


        vertex_buffer_data[j++] = front[(3*(i+1))%12];
        vertex_buffer_data[j++] = front[(3*(i+1)+1)%12];
        vertex_buffer_data[j++] = front[(3*(i+1)+2)%12];
        
    }

    for(i = 0 ; i <= 2; i+=2)
    {
        vertex_buffer_data[j++] = front[(3*i)%12];
        vertex_buffer_data[j++] = front[(3*i+1)%12];
        vertex_buffer_data[j++] = front[(3*i+2)%12];

        vertex_buffer_data[j++] = front[(3*(i+1))%12];
        vertex_buffer_data[j++] = front[(3*(i+1)+1)%12];
        vertex_buffer_data[j++] = front[(3*(i+1)+2)%12];


        vertex_buffer_data[j++] = front[(3*(i+2))%12];
        vertex_buffer_data[j++] = front[(3*(i+2)+1)%12];
        vertex_buffer_data[j++] = front[(3*(i+2)+2)%12];


        vertex_buffer_data[j++] = back[(3*i)%12];
        vertex_buffer_data[j++] = back[(3*i+1)%12];
        vertex_buffer_data[j++] = back[(3*i+2)%12];

        vertex_buffer_data[j++] = back[(3*(i+1))%12];
        vertex_buffer_data[j++] = back[(3*(i+1)+1)%12];
        vertex_buffer_data[j++] = back[(3*(i+1)+2)%12];


        vertex_buffer_data[j++] = back[(3*(i+2))%12];
        vertex_buffer_data[j++] = back[(3*(i+2)+1)%12];
        vertex_buffer_data[j++] = back[(3*(i+2)+2)%12];
        
    }


    return vertex_buffer_data;
}

void Cuboid::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 1, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}

void Cuboid::set_position(float x, float y) {
    this->position = glm::vec3(x, 0, y);
}

void Cuboid::tick() {
    this->rotation += speed;
    // this->position.x -= speed/100;
    // this->position.y -= speed;
}


    // glm::mat4 model = glm::mat4(1.0f);

    // glm::mat4 rotate    = glm::rotate((float) (0 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // glm::mat4 translate = glm::translate(glm::vec3(0, -height/2, 0));
    // // rotate          = rotate * translate;
    // model = ( translate * rotate );

    // GLfloat *body = Cuboid::CuboidArray(length1, breadth1);
    // for(i = 0 ; i < 3*3*2 ; ++i){
    //    if(i%3 == 0){
    //         glm::vec4 v(body[i],body[i+1], body[i+2],1);
    //         v = model * v;
    //         vertex_buffer_data[j++] = v.x;
    //         vertex_buffer_data[j++] = v.y;
    //         vertex_buffer_data[j++] = v.z;
    //     }
    // }
    // free(body);
    
    // GLfloat *cbody = Cuboid::CuboidArray(breadth1, height);
    // rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // translate = glm::translate(glm::vec3(-breadth1/2, 0, 0));
    // // rotate          = rotate * translate;
    // model = (translate * rotate );
    // for(i = 0 ; i < 3*3*2 ; ++i) {
    //     if(i%3 == 0){
    //         glm::vec4 v(cbody[i],cbody[i+1], cbody[i+2],1);
    //         v = model * v;
    //         vertex_buffer_data[j++] = v.x;
    //         vertex_buffer_data[j++] = v.y;
    //         vertex_buffer_data[j++] = v.z;
    //     }
    // }
    // free(cbody);

    // GLfloat *bbody = Cuboid::CuboidArray(breadth1, height);
    // rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // translate = glm::translate(glm::vec3(breadth1/2, 0, 0));
    // // rotate          = rotate * translate;
    // model = (translate * rotate );
    // for(i = 0 ; i < 3*3*2 ; ++i){
    //    if(i%3 == 0){
    //         glm::vec4 v(body[i],body[i+1], body[i+2],1);
    //         v = model * v;
    //         vertex_buffer_data[j++] = v.x;
    //         vertex_buffer_data[j++] = v.y;
    //         vertex_buffer_data[j++] = v.z;
    //     }
    // }
    // free(body);
    
    // // GLfloat *cbody = Cuboid::CuboidArray(breadth1, height);
    // // rotate    = glm::rotate((float) (90 * M_PI / 180.0f), glm::vec3(0, 0, 1));
    // // // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    // // translate = glm::translate(glm::vec3(-breadth1/2, 0, 0));
    // // // rotate          = rotate * translate;
    // // model = (translate * rotate );
    // // for(i = 0 ; i < 3*3*2 ; ++i) {
    // //     if(i%3 == 0){
    // //         glm::vec4 v(cbody[i],cbody[i+1], cbody[i+2],1);
    // //         v = model * v;
    // //         vertex_buffer_data[j++] = v.x;
    // //         vertex_buffer_data[j++] = v.y;
    // //         vertex_buffer_data[j++] = v.z;
    // //     }
    // // }