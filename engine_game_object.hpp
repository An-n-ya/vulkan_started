#pragma once

#include "engine_model.hpp"

// std
#include <memory>

namespace engine
{

    struct Transform2dComponent
    {
        glm::vec2 translation{}; // (position offset)
        glm::vec2 scale{1.f, 1.f};
        float rotation;

        glm::mat2 mat2()
        {
            const float s = glm::sin(rotation);
            const float c = glm::cos(rotation);
            glm::mat2 rotMatrix{{c, s}, {-s, c}};

            glm::mat2 scaleMat{{scale.x, .0f}, {.0f, scale.y}};
            return rotMatrix * scaleMat;
        }
    };

    class EngineGameObject
    {
    public:
        using id_t = unsigned int;

        static EngineGameObject createGameObject()
        {
            static id_t currentId = 0;
            return EngineGameObject{currentId++};
        }

        EngineGameObject(const EngineGameObject &) = delete;
        EngineGameObject &operator=(const EngineGameObject &) = delete;
        EngineGameObject(EngineGameObject &&) = default;
        EngineGameObject &operator=(EngineGameObject &&) = default;

        id_t getId() { return id; }

        std::shared_ptr<EngineModel> model{};
        glm::vec3 color{};
        Transform2dComponent transform2d{};

    private:
        EngineGameObject(id_t objId) : id{objId} {}

        id_t id;
    };
} // namespace engine