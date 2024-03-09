#pragma once

#include <string>
#include <vector>

#include "engine_device.hpp"

namespace engine
{
    struct PipelineConfigInfo
    {
        VkViewport viewport;
        VkRect2D scissor;
        VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
        VkPipelineRasterizationStateCreateInfo rasterizationInfo;
        VkPipelineMultisampleStateCreateInfo multisampleInfo;
        VkPipelineColorBlendAttachmentState colorBlendAttachment;
        VkPipelineColorBlendStateCreateInfo colorBlendInfo;
        VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
        VkPipelineLayout pipelineLayout = nullptr;
        VkRenderPass renderPass = nullptr;
        uint32_t subpass = 0;
    };

    class EnginePipeline
    {
    public:
        EnginePipeline(EngineDevice &device, const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configInfo);
        ~EnginePipeline();

        EnginePipeline(const EnginePipeline &) = delete;
        void operator=(const EnginePipeline &) = delete;

        void bind(VkCommandBuffer commandBuffer);

        static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);

    private:
        static std::vector<char>
        readFile(const std::string &filepath);

        void createGraphicsPipeline(const std::string &vertFilepath, const std::string &fragFilepath, const PipelineConfigInfo &configInfo);

        void createShaderModule(const std::vector<char> &code, VkShaderModule *shaderModule);
        EngineDevice &engineDevice;
        VkPipeline graphicsPipeline;
        VkShaderModule vertShaderModule;
        VkShaderModule fragShaderModule;
    };
}