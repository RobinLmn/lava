#include "CameraControlSystem.hpp"

#include <core/Engine.hpp>
#include <core/input/Key.hpp>
#include <util/Math.hpp>

#include <gameplay/components/TransformComponent.hpp>
#include <gameplay/components/CameraComponent.hpp>

namespace lava
{
    CameraControlSystem::CameraControlSystem( entt::registry* registry )
        : System( registry )
    {
        auto onMouseMove = [registry](float dx, float dy)
        {
            auto entities = registry->view<CameraComponent, TransformComponent>().each();
            for (auto [entity, camera, transform] : entities)
            {
                if (!camera.isMainCamera) continue;
                if (!Engine::isKeyPressed( Key::LControl )) return;
                
                transform.rotation += {dy, dx, 0};
                return;
            }
        };
        
        auto onMouseScroll = [registry](float dx, float dy)
        {
            auto entities = registry->view<CameraComponent>().each();
            for (auto [entity, camera] : entities)
            {
                if (!camera.isMainCamera) continue;
                
                camera.fov += dy * camera.sensitivity;
                return;
            }
        };
        
        Engine::setOnMouseMove( onMouseMove );
        Engine::setOnMouseScroll( onMouseScroll );
    }

    auto CameraControlSystem::update( double dt ) -> void
    {
        auto entities = registry->view<CameraComponent, TransformComponent>().each();
        for (auto [entity, camera, transform] : entities)
        {
            if (!camera.isMainCamera) continue;
            
            if (Engine::isKeyPressed( Key::W )) transform.position.z += camera.speed * dt * 20.f;
            if (Engine::isKeyPressed( Key::S )) transform.position.z -= camera.speed * dt * 20.f;
            if (Engine::isKeyPressed( Key::A )) transform.position.x += camera.speed * dt;
            if (Engine::isKeyPressed( Key::D )) transform.position.x -= camera.speed * dt;
            if (Engine::isKeyPressed( Key::Space )) transform.position.y -= camera.speed * dt * 0.2f;
            if (Engine::isKeyPressed( Key::LShift )) transform.position.y += camera.speed * dt * 0.2f;
            
            return;
        }
    }
}
