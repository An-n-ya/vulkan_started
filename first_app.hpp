#pragma once

#include "engine_window.hpp"
#include "engine_pipeline.hpp"
#include "engine_pipeline.hpp"
#include "engine_swap_chain.hpp"
#include "engine_model.hpp"

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
        void loadModels();
        void createPipelineLayout();
        void createPipeline();
        void createCommandBuffer();
        void drawFrame();
        EngineWindow engineWindow{WIDTH, HEIGHT, "hello vulkan"};
        EngineDevice engineDevice{engineWindow};
        EngineSwapChain engineSwapChain{engineDevice, engineWindow.getExtent()};
        // EnginePipeline enginePipeline{engineDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", EnginePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
        std::unique_ptr<EnginePipeline> enginePipeline;
        VkPipelineLayout pipelineLayout;
        std::vector<VkCommandBuffer> commandBuffers;
        std::unique_ptr<EngineModel> engineModel;
    };
}