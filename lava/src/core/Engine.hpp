#pragma once

#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include <core/Window.hpp>
#include <renderer/View.hpp>
#include <core/input/Input.hpp>
#include <core/input/Key.hpp>
#include <gameplay/World.hpp>
#include <core/System.hpp>

namespace lava
{
    class Engine final
    {
    public:
        Engine( Engine&& ) = delete;
        Engine( const Engine& ) = delete;
        Engine operator=( const Engine& ) = delete;
        
    public:
        
        [[nodiscard]] static auto get() -> Engine&;
        [[nodiscard]] static auto getDevice() -> MTL::Device*;
        
        static auto isKeyPressed( Key ) -> bool;
        static auto setOnMouseScroll( std::function<void(float, float)> ) -> void;
        static auto setOnMouseMove( std::function<void(float, float)> ) -> void;
        
        auto run() -> void;
        auto initialize() -> void;
        auto update() -> void;
        auto shutdown() -> void;
     
    private:
        Engine() = default;
        
    private:
        Window* window;
        MTL::Device* device;
        View* view;
        World* world;
        Input* input;
        
        std::chrono::high_resolution_clock* clock;
        std::chrono::steady_clock::time_point lastTime;
        
    private:
        class AppDelegate final : public NS::ApplicationDelegate
        {
        public:
            ~AppDelegate();
            
        private:
            auto applicationWillFinishLaunching( NS::Notification* ) -> void override;
            auto applicationDidFinishLaunching( NS::Notification* ) -> void override;
            auto applicationShouldTerminateAfterLastWindowClosed( NS::Application* ) -> bool override;
        };
    };
}
