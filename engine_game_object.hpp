#pragma once

#include "engine_model.hpp"
#include <glm/gtc/matrix_transform.hpp>
// std
#include <memory>

namespace engine
{

    struct TransformComponent
    {
        glm::vec3 translation{}; // (position offset)
        glm::vec3 scale{1.f, 1.f, 1.f};
        glm::vec3 rotation{};

        glm::mat4 mat4();
        glm::mat3 normalMatrix();
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
        TransformComponent transform{};

    private:
        EngineGameObject(id_t objId) : id{objId} {}

        id_t id;
    };
} // namespace engine