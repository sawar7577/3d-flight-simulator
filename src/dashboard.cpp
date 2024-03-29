#include "main.h"
#include "dashboard.h"
#include "crosshair.h"
#include "fuel.h"
#include "airplane.h"
#include "speedometer.h"
#include "score.h"

Dashboard::Dashboard(float x, float y, float z) {
    this->position = glm::vec3(x, y, z);
    this->rotate = glm::mat4(1.0f);
    GLfloat vertex_buffer_data[1000001];
    int j = 0;
    this->cross = Crosshair(0,0,0);
    this->cp = Compass(25,-25,0);
    this->f = Fuel(0,-27,0);
    this->ap = Altimeter(25,0,0);
    this->sp = Speedometer(0,-25,0);
    this->sc = Score(25,25,0);
    this->hc = Score(-25,20,0);
}

void Dashboard::draw(glm::mat4 VP) {
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
    cross.draw(VP);
    f.draw(VP);
    cp.draw(VP);
    ap.draw(VP);
    sp.draw(VP);
    sc.draw(VP);
    hc.draw(VP);
}

void Dashboard::tick(Airplane &air) {
    this->f.tick(air.fvalue);
    this->cp.changeOrientation(air);
    this->ap.changeHeight(air);
    this->sp.changeSpeed(air);
    this->sc.changeScore(air.score);
    this->hc.changeScore(air.health);
}

void Dashboard::setCrosshair(bool flag) {
    this->cross.changeColor(flag);
}