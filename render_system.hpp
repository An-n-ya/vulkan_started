
#pragma once

#include "engine_device.hpp"
#include "engine_game_object.hpp"
#include "engine_pipeline.hpp"
#include "engine_camera.hpp"

// std
#include <memory>
#include <vector>

namespace engine
{
    class SimpleRenderSystem
    {
    public:
        SimpleRenderSystem(EngineDevice &device, VkRenderPass renderPass);
        ~SimpleRenderSystem();

        SimpleRenderSystem(const SimpleRenderSystem &) = delete;
        SimpleRenderSystem &operator=(const SimpleRenderSystem &) = delete;

        void renderGameObjects(VkCommandBuffer commandBuffer, std::vector<EngineGameObject> &gameObjects, const EngineCamera camera);

    private:
        void createPipelineLayout();
        void createPipeline(VkRenderPass renderPass);

        EngineDevice &engineDevice;

        std::unique_ptr<EnginePipeline> enginePipeline;
        VkPipelineLayout pipelineLayout;
    };
} // namespace engine