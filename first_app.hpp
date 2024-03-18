#pragma once

#include "engine_device.hpp"
#include "engine_game_object.hpp"
#include "engine_pipeline.hpp"
#include "engine_swap_chain.hpp"
#include "engine_window.hpp"

// std
#include <memory>
#include <vector>

namespace engine
{
    class FirstApp
    {
    public:
        static constexpr int WIDTH = 800;
        static constexpr int HEIGHT = 600;

        FirstApp();
        ~FirstApp();

        FirstApp(const FirstApp &) = delete;
        FirstApp &operator=(const FirstApp &) = delete;

        void run();

    private:
        void loadGameObjects();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffers();
        void drawFrame();
        void recreateSwapChain();
        void recordCommandBuffer(int imageIndex);
        void renderGameObjects(VkCommandBuffer commandBuffer);

        EngineWindow engineWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        EngineDevice engineDevice{engineWindow};
        std::unique_ptr<EngineSwapChain> engineSwapChain;
        std::vector<EngineGameObject> gameObjects;
        std::unique_ptr<EnginePipeline> enginePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
    };
} // namespace engine