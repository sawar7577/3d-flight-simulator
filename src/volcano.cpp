
#include "volcano.h"
#include "main.h"


float arrv[3000][3000];
inline static float randomv(int range)
{
    int ret = (rand() % (range * 50)) - range;
    ret = std::max(ret, -50);
    ret = std::min(ret, 50);
    return ret;
}
float mxv;
float mnv;
void algo_stepv(int x, int y, int size, int cnt) {
    if(size <= 2){
        return;
    }
    arrv[x+size/2][y+size/2] = (arrv[x][y] + arrv[x+2*(size/2)][y] + 
    arrv[x][y+2*(size/2)] + arrv[x+2*(size/2)][y+2*(size/2)])/4;
    if(cnt == 0)
        arrv[x+size/2][y+size/2] += randomv(size);

    arrv[x+size/2][y+size/2] = std::min(mxv, arrv[x+size/2][y+size/2]);
    arrv[x+size/2][y+size/2] = std::max(mnv, arrv[x+size/2][y+size/2]);

    
    //Diamond steps
    arrv[x+size/2][y]            = (arrv[x][y] + arrv[x+size/2][y+size/2] + arrv[x+2*(size/2)][y])/3;
    arrv[x+size/2][y] = std::min(mxv, arrv[x+size/2][y]);
    arrv[x+size/2][y] = std::max(mnv, arrv[x+size/2][y]);



    arrv[x+2*(size/2)][y+size/2] = (arrv[x][y+2*(size/2)] + arrv[x+size/2][y+size/2] + arrv[x+2*(size/2)][y+2*(size/2)])/3;
    arrv[x+2*(size/2)][y+size/2] = std::min(mxv, arrv[x+2*(size/2)][y+size/2]);
    arrv[x+2*(size/2)][y+size/2] = std::max(mnv, arrv[x+2*(size/2)][y+size/2]);



    arrv[x][y+size/2]            = (arrv[x][y] + arrv[x+size/2][y+size/2] + arrv[x][y+2*(size/2)])/3;
    arrv[x][y+size/2] = std::min(mxv, arrv[x][y+size/2]);
    arrv[x][y+size/2] = std::max(mnv, arrv[x][y+size/2]);



    arrv[x+size/2][y+2*(size/2)] = (arrv[x][y+2*(size/2)] + arrv[x+size/2][y+size/2] + arrv[x+2*(size/2)][y+2*(size/2)])/3;
    arrv[x+size/2][y+2*(size/2)] = std::min(mxv, arrv[x+size/2][y+2*(size/2)]);
    arrv[x+size/2][y+2*(size/2)] = std::max(mnv, arrv[x+size/2][y+2*(size/2)]);



    //algo steps
    algo_stepv(x,y,size/2 + 1, cnt + 1);
    algo_stepv(x+size/2,y,size/2 + 1, cnt + 1);
    algo_stepv(x,y+size/2,size/2 + 1, cnt + 1);
    algo_stepv(x+size/2,y+size/2,size/2 + 1, cnt + 1);

}

Volcano::Volcano(int x, int y, int z, int width) {
    this->position = glm::vec3(x, y, z);
    this->rotation = 0.0f;
    float scale = 1.0f;
    float scale2 = 1.0f;
    this->kill = false;

    srand(0);
    arrv[1][1] = arrv[1][width] = arrv[width][1] = arrv[width][width] = 0;
    arrv[1+width/2][1+width/2] = width;
    mxv = width;
    mnv = -width;
    algo_stepv(1,1,width,0);   
    int i,j,k;
    j = 0;
    GLfloat vertex_buffer_data[5000000];
    for(i = 1; i < width ; ++i) {
        for(k = 1; k < width ; ++k){

            if(i%2 == 1){
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arrv[i][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arrv[i][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arrv[i+1][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);

                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arrv[i+1][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arrv[i+1][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * (i+2);
                vertex_buffer_data[j++] =  scale * arrv[i+2][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
            }
            else {
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arrv[i][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arrv[i][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * (i-1);
                vertex_buffer_data[j++] =  scale * arrv[i-1][k];
                vertex_buffer_data[j++] =  scale2 *k;


                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arrv[i+1][k];
                vertex_buffer_data[j++] =  scale2 * k;
                
                vertex_buffer_data[j++] =  scale2 * (i+1);
                vertex_buffer_data[j++] =  scale * arrv[i+1][k+1];
                vertex_buffer_data[j++] =  scale2 * (k+1);
                
                vertex_buffer_data[j++] =  scale2 * i;
                vertex_buffer_data[j++] =  scale * arrv[i][k];
                vertex_buffer_data[j++] =  scale2 * k;
            }

        }
    }
    GLfloat *color_buffer_data = new GLfloat[j];

    for(int i = 0 ; i < j/3 ; ++i) {
        color_buffer_data[3*i] = vertex_buffer_data[3*i+1]/mxv;
        color_buffer_data[3*i+1] = 0.1f;
        color_buffer_data[3*i+2] = 0.1f;
    }

    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, color_buffer_data, GL_FILL);
}

void Volcano::draw(glm::mat4 VP) {
    Matrices.model = glm::mat4(1.0f);
    glm::mat4 translate = glm::translate (this->position);    // glTranslatef
    glm::mat4 rotate    = glm::rotate((float) (this->rotation * M_PI / 180.0f), glm::vec3(1, 0, 0));
    // No need as coords centered at 0, 0, 0 of cube arouund which we waant to rotate
    rotate          = rotate * glm::translate(glm::vec3(0, -0.6, 0));
    Matrices.model *= (translate * rotate);
    glm::mat4 MVP = VP * Matrices.model;
    glUniformMatrix4fv(Matrices.MatrixID, 1, GL_FALSE, &MVP[0][0]);
    draw3DObject(this->object);
}


void Volcano::tick() {

}
