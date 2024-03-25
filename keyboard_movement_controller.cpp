#include "keyboard_movement_controller.hpp"
#include <limits>

namespace engine
{
    void KeyboardMovementController::moveInPlaneXZ(GLFWwindow *window, float dt, EngineGameObject &gameObject)
    {
        glm::vec3 rotate{0.f};
        if (glfwGetKey(window, keys.lookRight) == GLFW_PRESS)
            rotate.y += 1.f;
        if (glfwGetKey(window, keys.lookDown) == GLFW_PRESS)
            rotate.x -= 1.f;
        if (glfwGetKey(window, keys.lookLeft) == GLFW_PRESS)
            rotate.y -= 1.f;
        if (glfwGetKey(window, keys.lookUp) == GLFW_PRESS)
            rotate.x += 1.f;

        if (glm::dot(rotate, rotate) > std::numeric_limits<float>::epsilon())
        {
            gameObject.transform.rotation += lookSpeed * dt * glm::normalize(rotate);
        }

        gameObject.transform.rotation.x = glm::clamp(gameObject.transform.rotation.x, -1.5f, 1.5f);
        gameObject.transform.rotation.y = glm::mod(gameObject.transform.rotation.y, glm::two_pi<float>());

        float yaw = gameObject.transform.rotation.y;
        const glm::vec3 forward_direction{sin(yaw), 0.f, cos(yaw)};
        const glm::vec3 right_direction{cos(yaw), 0.f, -sin(yaw)};
        const glm::vec3 up_direction{0.f, -1.f, 0.f};
        glm::vec3 move{0.f};
        if (glfwGetKey(window, keys.moveForward) == GLFW_PRESS)
            move += forward_direction;
        if (glfwGetKey(window, keys.moveBackward) == GLFW_PRESS)
            move -= forward_direction;
        if (glfwGetKey(window, keys.moveLeft) == GLFW_PRESS)
            move -= right_direction;
        if (glfwGetKey(window, keys.moveRight) == GLFW_PRESS)
            move += right_direction;
        if (glfwGetKey(window, keys.moveUp) == GLFW_PRESS)
            move += up_direction;
        if (glfwGetKey(window, keys.moveDown) == GLFW_PRESS)
            move -= up_direction;

        if (glm::dot(move, move) > std::numeric_limits<float>::epsilon())
            gameObject.transform.translation += moveSpeed * dt * glm::normalize(move);
    }
}