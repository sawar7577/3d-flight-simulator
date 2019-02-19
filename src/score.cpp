#include "main.h"
#include "score.h"


std::vector <std::string> hsh;


int Score::giveCount(std::string hash) {
    int count = 0;
    for(int i = 0 ; i < hash.length() ; ++i) {
        if(hash[i] == '1') {
            count++;
        }
    }
    return count;
}

GLfloat * Score::giveNumber(std::string hash) {
   
    int count = this->giveCount(hash);
    GLfloat * score_data = (GLfloat *)malloc(sizeof(GLfloat) * 6*6*3 * count);
    int j = 0;
    float h_height = 0.5f;
    float h_length = 2.0f;
    float h_width = 0.0f;

    float v_height = 2.0f;
    float v_length = 0.5f;
    float v_width = 0.0f;
    if(hash[0] == '1') {
        GLfloat * rec = Cuboid::CuboidArray(v_length, v_length, 0.0f, 0.0, v_height);
        for(int i = 0 ; i < 6*6*3 ; ++i) {
            if(i%3 == 0) {
                score_data[j++] = rec[i] - h_length/2;
            }
            else if(i%3 == 1) {
                score_data[j++] = rec[i] - v_height/2;
            }
            else {
                score_data[j++] = rec[i];
            }
        }
        free(rec);
	}
	if(hash[1] == '1') {
        GLfloat * rec = Cuboid::CuboidArray(v_length, v_length, 0.0f, 0.0, v_height);            
            for(int i = 0 ; i < 6*6*3 ; ++i) {
            if(i%3 == 0) {
                score_data[j++] = rec[i] + h_length/2;
            }
            else if(i%3 == 1) {
                score_data[j++] = rec[i] - v_height/2;
            }
            else {
                score_data[j++] = rec[i];
            }
        }
        free(rec);
	}
	if(hash[2] == '1') {
        GLfloat * rec = Cuboid::CuboidArray(v_length, v_length, 0.0f, 0.0, v_height);

        for(int i = 0 ; i < 6*6*3 ; ++i) {
            if(i%3 == 0) {
                score_data[j++] = rec[i] - h_length/2;
            }
            else if(i%3 == 1) {
                score_data[j++] = rec[i] + v_height/2;
            }
            else {
                score_data[j++] = rec[i];
            }
        }
        free(rec);
	}
	if(hash[3] == '1') {
        GLfloat * rec = Cuboid::CuboidArray(v_length, v_length, 0.0f, 0.0, v_height);

        for(int i = 0 ; i < 6*6*3 ; ++i) {
            if(i%3 == 0) {
                score_data[j++] = rec[i] + h_length/2;
            }
            else if(i%3 == 1) {
                score_data[j++] = rec[i] + v_height/2;
            }
            else {
                score_data[j++] = rec[i];
            }
        }
        free(rec);
	}
	if(hash[4] == '1') {
        GLfloat * rec = Cuboid::CuboidArray(h_length, h_length, 0.0f, 0.0, h_height);
        for(int i = 0 ; i < 6*6*3 ; ++i) {
            if(i%3 == 0) {
                score_data[j++] = rec[i];
            }
            else if(i%3 == 1) {
                score_data[j++] = rec[i] - v_height;
            }
            else {
                score_data[j++] = rec[i];
            }
        }
        free(rec);
	}
	if(hash[5] == '1') {
        GLfloat * rec = Cuboid::CuboidArray(h_length, h_length, 0.0f, 0.0, h_height);

        for(int i = 0 ; i < 6*6*3 ; ++i) {
            if(i%3 == 0) {
                score_data[j++] = rec[i];
            }
            else if(i%3 == 1) {
                score_data[j++] = rec[i];
            }
            else {
                score_data[j++] = rec[i];
            }
        }
        free(rec);
	}
	if(hash[6] == '1') {
        GLfloat * rec = Cuboid::CuboidArray(h_length, h_length, 0.0f, 0.0, h_height);

        for(int i = 0 ; i < 6*6*3 ; ++i) {
            if(i%3 == 0) {
                score_data[j++] = rec[i];
            }
            else if(i%3 == 1) {
                score_data[j++] = rec[i] + v_height;
            }
            else {
                score_data[j++] = rec[i];
            }
        }
        free(rec);
	}
    return score_data;
}


Score::Score(float x, float y, float z) {
    hsh.push_back("1111101");
    hsh.push_back("0101000");
    hsh.push_back("1001111");
    hsh.push_back("0101111");
    hsh.push_back("0111010");
    hsh.push_back("0110111");
    hsh.push_back("1110111");
    hsh.push_back("0101001");    
    hsh.push_back("1111111");
    hsh.push_back("0111011");
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[1000001];
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
}

void Score::draw(glm::mat4 VP) {
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
}

void Score::changeScore(int numb) {
    free(this->object);
    int score = numb;
    GLfloat vertex_buffer_data[1000001];
    int j = 0;
    float adder = 0.0f;
    for(int i = 0 ; score != 0 ; ++i) {
        GLfloat * num = giveNumber(hsh[score%10]);
        int cnte = this->giveCount(hsh[score%10]);
        // std::cout  << cnte << std::endl;
        for(int k = 0 ; k < 6*6*3*cnte ; ++k){
            if(k%3 == 0) {
                vertex_buffer_data[j++] = num[k] - adder;                
            }
            else {
                vertex_buffer_data[j++] = num[k];
            }
        }
        score /= 10;
        adder += 3.0f;
        free(num);
    }
    this->object = create3DObject(GL_TRIANGLES, j/3, vertex_buffer_data, COLOR_BLACK, GL_FILL);    
}