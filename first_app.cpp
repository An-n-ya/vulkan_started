#include "first_app.hpp"
#include <stdexcept>

namespace engine
{

    FirstApp::FirstApp()
    {
        loadModels();
        createPipelineLayout();
        createPipeline();
        createCommandBuffer();
    }
    FirstApp::~FirstApp()
    {
        vkDestroyPipelineLayout(engineDevice.device(), pipelineLayout, nullptr);
    }

    void FirstApp::run()
    {
        while (!engineWindow.shouldClose())
        {
            glfwPollEvents();
            drawFrame();
        }

        vkDeviceWaitIdle(engineDevice.device());
    }
    void FirstApp::loadModels()
    {
        std::vector<EngineModel::Vertex> vertices{
            {{0.0f, -0.5f}},
            {{0.5f, 0.5f}},
            {{-0.5f, 0.5f}},
        };

        engineModel = std::make_unique<EngineModel>(engineDevice, vertices);
    }

    void FirstApp::createPipelineLayout()
    {
        VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
        pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
        pipelineLayoutInfo.setLayoutCount = 0;
        pipelineLayoutInfo.pSetLayouts = nullptr;
        pipelineLayoutInfo.pushConstantRangeCount = 0;
        pipelineLayoutInfo.pPushConstantRanges = nullptr;
        if (vkCreatePipelineLayout(engineDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create pipeline layout");
        }
    }

    void FirstApp::createPipeline()
    {
        auto pipelineConfig = EnginePipeline::defaultPipelineConfigInfo(engineSwapChain.width(), engineSwapChain.height());
        pipelineConfig.renderPass = engineSwapChain.getRenderPass();
        pipelineConfig.pipelineLayout = pipelineLayout;
        enginePipeline = std::make_unique<EnginePipeline>(engineDevice, "shaders/simple_shader.vert.spv", "shaders/simple_shader.frag.spv", pipelineConfig);
    }
    void FirstApp::createCommandBuffer()
    {
        commandBuffers.resize(engineSwapChain.imageCount());

        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandPool = engineDevice.getCommandPool();
        allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
        if (vkAllocateCommandBuffers(engineDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate command buffers");
        }

        for (int i = 0; i < commandBuffers.size(); i++)
        {
            VkCommandBufferBeginInfo beginInfo{};
            beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
            if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to begin recording command buffer");
            }

            VkRenderPassBeginInfo renderPassInfo{};
            renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
            renderPassInfo.renderPass = engineSwapChain.getRenderPass();
            renderPassInfo.framebuffer = engineSwapChain.getFrameBuffer(i);

            renderPassInfo.renderArea.offset = {0, 0};
            renderPassInfo.renderArea.extent = engineSwapChain.getSwapChainExtent();

            std::array<VkClearValue, 2> clearValues{};
            clearValues[0].color = {0.1f, 0.1f, 0.1f, 0.1f};
            clearValues[1].depthStencil = {1.0f, 0};

            renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
            renderPassInfo.pClearValues = clearValues.data();

            vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

            enginePipeline->bind(commandBuffers[i]);
            // vkCmdDraw(commandBuffers[i], 3, 1, 0, 0);
            engineModel->bind(commandBuffers[i]);
            engineModel->draw(commandBuffers[i]);

            vkCmdEndRenderPass(commandBuffers[i]);
            if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS)
            {
                throw std::runtime_error("failed to record command buffer");
            }
        }
    }
    void FirstApp::drawFrame()
    {
        uint32_t imageIndex;
        auto result = engineSwapChain.acquireNextImage(&imageIndex);

        if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR)
        {
            throw std::runtime_error("failed to acquire swap chain image");
        }

        result = engineSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to present swap chain image");
        }
    }
}