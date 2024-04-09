#pragma once
#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera
{
public:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_right;
    glm::vec3 m_up;
    // yah pitch roll
    glm::vec3 m_rotation;

    Camera(glm::vec3 position, glm::vec3 rotation);
    ~Camera();
    
    glm::mat4 getViewMatrix();

    void setPosition(glm::vec3 position);
    void setRotation(glm::vec3 rotation);

    glm::vec3 getPosition();
    glm::vec3 getRotation();
    glm::vec3 getFront();
    glm::vec3 getRight();
};

#endif