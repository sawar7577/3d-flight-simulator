#include "cuboid.h"
#include "main.h"

bool checkCollision(Cuboid A, glm::mat4 rotateA, Cuboid B, glm::mat4 rotateB) {

    std::vector <glm::vec3> axisA, axisB;
    axisA = getAxis(A, rotateA);
    axisA = getAxis(B, rotateB);
    for(int i = 0 ; i < axisA.size() ; ++i) {
        if(checkAxis(axisA[i], A, rotateA, B, rotateB)){
            return true;
        }
    }

    for(int i = 0 ; i < axisB.size() ; ++i) {
        if(checkAxis(axisB[i], A, rotateA, B, rotateB)){
            return true;
        }
    }

    for(int i = 0 ; i < axisA.size() ; ++i) {
        for(int j = 0 ; j < axisB.size() ; ++j) {
            if(checkAxis(glm::cross(axisA[i],axisB[j]), A, rotateA, B, rotateB)){
                return true;
            }
        }
    }
    return false;
}

bool checkAxis(glm::vec3 axis, Cuboid A, glm::mat4 rotateA, Cuboid B, glm::mat4 rotateB) {
    std::pair <float, float> rangeA;
    std::pair <float, float> rangeB;
    glm::vec3 point;

    point = glm::vec3(rotateA * glm::vec4(A.length1/2, A.breadth1/2, A.height/2, 1));
    rangeA.first = std::min(rangeA.first, getProjection(axis, point));
    rangeA.second = std::max(rangeA.second, getProjection(axis, point));

}

float getProjection(glm::vec3 axis, glm::vec3 point) {
    // return (glm::dot(axis, point)/glm::dot(axis, axis))*axis;
}

std::vector <glm::vec3> getAxis(Cuboid A, glm::mat4 rotateA) {
    std::vector <glm::vec3> ans;
    ans.push_back(glm::vec3(rotateA * glm::vec4(1,0,0,1)));
    ans.push_back(glm::vec3(rotateA * glm::vec4(0,1,0,1)));
    ans.push_back(glm::vec3(rotateA * glm::vec4(0,0,1,1)));
    return ans;
}