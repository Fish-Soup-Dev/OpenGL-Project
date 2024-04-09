#include "camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 rotation)
{
    m_position = position;
    m_rotation = rotation;
    m_up = glm::vec3(0.0f, 1.0f, 0.0f);
    m_front = glm::vec3(0.0f, 0.0f, -1.0f);
}

Camera::~Camera()
{

}

glm::mat4 Camera::getViewMatrix()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
    direction.y = sin(glm::radians(m_rotation.y));
    direction.z = sin(glm::radians(m_rotation.x)) * cos(glm::radians(m_rotation.y));
    m_front = glm::normalize(direction);

    glm::mat4 roll_mat = glm::rotate(glm::mat4(1.0f), glm::radians(m_rotation.z), m_front);
    m_up = glm::mat3(roll_mat) * m_up;

    m_right = glm::normalize(glm::cross(m_front, m_up));

    return glm::lookAt(m_position, m_position + m_front, m_up);
}

void Camera::setPosition(glm::vec3 position)
{
    m_position = position;
}

void Camera::setRotation(glm::vec3 rotation)
{
    m_rotation = rotation;
}

glm::vec3 Camera::getPosition()
{
    return m_position;
}

glm::vec3 Camera::getRotation()
{
    return m_rotation;
}

glm::vec3 Camera::getFront()
{
    return m_front;
}

glm::vec3 Camera::getRight()
{
    return m_right;
}