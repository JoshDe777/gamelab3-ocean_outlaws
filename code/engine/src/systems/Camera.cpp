
#include "engine/systems/Camera.h"
#include "engine/Game.h"

namespace EisEngine::systems {
    Camera::Camera(EisEngine::Game &engine, const Vector2& screenDimensions): System(engine),
    m_screenWidth((int) screenDimensions.x), m_screenHeight((int) screenDimensions.y),
    aspectRatio(screenDimensions.x / screenDimensions.y) {
        entity = &engine.entityManager.createEntity("Camera");
        transform = entity->transform;
        engine.onUpdate.addListener([&] (Game &game){
            // save old known window dimensions.
            int oldWidth = m_screenWidth;
            int oldHeight = m_screenHeight;

            // get current window dimensions
            auto dimensions = game.context.GetWindowSize();
            m_screenWidth = (int) dimensions.x;
            m_screenHeight = (int) dimensions.y;

            // return if no changes
            if(oldWidth == m_screenWidth && oldHeight == m_screenHeight) return;

            // if changes update aspect ratio and m_zoom factor.
            UpdateAspectRatio();
        });
    }

    glm::mat4 Camera::GetVPMatrix() {
        auto view = CalculateViewMatrix();
        auto projection = GetProjectionMatrix();
        return projection * view;
    }

    glm::mat4 Camera::CalculateViewMatrix() const {
        glm::vec3 cameraPos = (glm::vec3) transform->GetGlobalPosition();
        // (facing negative Z at rotation (0, 0, 0))
        glm::vec3 cameraDir = -(glm::vec3) transform->Forward();
        glm::vec3 upDir = (glm::vec3) transform->Up();
        glm::vec3 viewVector = cameraPos + cameraDir;

        return glm::lookAt(cameraPos, viewVector, upDir);
    }

    glm::mat4 Camera::GetProjectionMatrix() const {
        return glm::ortho(-aspectRatio / m_zoom,
                          aspectRatio / m_zoom,
                          -1.0f / m_zoom,
                          1.0f / m_zoom,
                          nearClip,
                          farClip);
    }
}
