#pragma once

#include "engine_device.hpp"
#include "engine_game_object.hpp"
#include "engine_window.hpp"
#include "engine_renderer.hpp"

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

        EngineWindow engineWindow{WIDTH, HEIGHT, "Hello Vulkan!"};
        EngineDevice engineDevice{engineWindow};
        EngineRenderer engineRenderer{engineWindow, engineDevice};
        std::vector<EngineGameObject> gameObjects;
    };
} // namespace engine