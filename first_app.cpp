#include "first_app.hpp"
#include "render_system.hpp"
#include "engine_camera.hpp"
#include "keyboard_movement_controller.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
// std
#include <array>
#include <cassert>
#include <chrono>
#include <stdexcept>
#include <iostream>
namespace engine
{
    FirstApp::FirstApp()
    {
        loadGameObjects();
    }

    FirstApp::~FirstApp() {}

    void FirstApp::run()
    {
        // std::cout << "maxPushConstants: "
        //           << engineDevice.properties.limits.maxPushConstantsSize
        //           << "" << std::endl;
        SimpleRenderSystem simpleRenderSystem{engineDevice, engineRenderer.getSwapChainRenderPass()};
        EngineCamera camera{};

        // camera.setViewDirection(glm::vec3{0.f}, glm::vec3{0.0f, 0.f, -1.f});
        auto viewerObject = EngineGameObject::createGameObject();
        KeyboardMovementController cameraController{};

        auto oldTime = std::chrono::high_resolution_clock::now();
        while (!engineWindow.shouldClose())
        {

            auto currentTime = std::chrono::high_resolution_clock::now();
            float frameTime = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - oldTime).count();
            oldTime = currentTime;

            cameraController.moveInPlaneXZ(engineWindow.getWindow(), frameTime, viewerObject);
            camera.setViewXYZ(viewerObject.transform.translation, viewerObject.transform.rotation);

            float aspect = engineRenderer.getAspectRatio();
            // camera.setOrthographicProjection(-aspect, aspect, -1, 1, -1, 1);
            camera.setPerspectiveProjection(glm::radians(50.f), aspect, 0.1f, 10.f);
            glfwPollEvents();
            if (auto commandBuffer = engineRenderer.beginFrame())
            {
                engineRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects, camera);
                engineRenderer.endSwapChainRenderPass(commandBuffer);
                engineRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(engineDevice.device());
    }

    void FirstApp::loadGameObjects()
    {
        std::shared_ptr<EngineModel> engineModel = EngineModel::createModelFromFile(engineDevice, "models/smooth_vase.obj");

        auto gameObj = EngineGameObject::createGameObject();
        gameObj.model = engineModel;
        gameObj.transform.translation = {.0f, .0f, 2.0f};
        gameObj.transform.scale = glm::vec3{3.0f};

        gameObjects.push_back(std::move(gameObj));
    }

} // namespace engine