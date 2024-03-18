#include "first_app.hpp"
#include "render_system.hpp"

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/gtc/constants.hpp>
#include <glm/glm.hpp>
// std
#include <array>
#include <cassert>
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

        while (!engineWindow.shouldClose())
        {
            glfwPollEvents();
            if (auto commandBuffer = engineRenderer.beginFrame())
            {
                engineRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
                engineRenderer.endSwapChainRenderPass(commandBuffer);
                engineRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(engineDevice.device());
    }

    void FirstApp::loadGameObjects()
    {
        std::vector<EngineModel::Vertex> vertices{
            {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
            {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
            {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}};
        auto engineModel = std::make_shared<EngineModel>(engineDevice, vertices);

        auto triangle = EngineGameObject::createGameObject();
        triangle.model = engineModel;
        triangle.color = {.1f, .7f, .2f};
        triangle.transform2d.translation.x = .2f;
        triangle.transform2d.scale = {2.f, .5f};
        triangle.transform2d.rotation = .25f * glm::two_pi<float>();

        gameObjects.push_back(std::move(triangle));
    }

} // namespace engine