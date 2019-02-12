#include "main.h"
#include "parachute.h"

Parachute::Parachute(float x, float y, float z) : Enemy(x, y, z) {

}

void Parachute::tick(){
    this->position += glm::vec3(0,-0.1f,0);
}