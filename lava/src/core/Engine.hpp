#pragma once

#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

#include <core/Window.hpp>
#include <renderer/View.hpp>

#include <gameplay/World.hpp>

namespace lava
{
    class Engine final
    {
    public:
        Engine( Engine&& ) = delete;
        Engine( const Engine& ) = delete;
        Engine operator=( const Engine& ) = delete;
        
    public:
        
        [[nodiscard]]
        static auto get() -> Engine& { static Engine engine; return engine; };
        
        [[nodiscard]]
        auto getDevice() -> MTL::Device* { return device; };
        
        auto run() -> void;
        auto initialize() -> void;
        auto shutdown() -> void;
     
    private:
        Engine() = default;
        
    private:
        Window* window;
        MTL::Device* device;
        View* view;
        World* world;
        
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
