#include "Engine.hpp"
#include <chrono>

namespace lava
{
    auto Engine::initialize() -> void
    {
        auto frame = (CGRect){ {100.0, 100.0}, {512.0, 512.0} };
        
        device = MTL::CreateSystemDefaultDevice();
        window = new Window( frame );
        world = new World();
        view = new View( frame, device, world );
        
        window->setWindowView(view->getView());
        world->begin();
    }

    auto Engine::run() -> void
    {
        AppDelegate delegate;
        
        auto* autoReleasePool = NS::AutoreleasePool::alloc()->init();
        auto* app = NS::Application::sharedApplication();
        
        clock = new std::chrono::high_resolution_clock();
        
        app->setDelegate( &delegate );
        app->run();

        autoReleasePool->release();
    }

    auto Engine::update() -> void
    {
        const auto deltaTime = std::chrono::duration_cast<std::chrono::seconds>(clock->now() - lastTime).count();
        lastTime = clock->now();
        
        world->update( deltaTime );
    }

    auto Engine::shutdown() -> void
    {
        world->end();
        device->release();
        
        delete window;
        delete view;
        delete world;
    }

    auto Engine::AppDelegate::applicationWillFinishLaunching( NS::Notification* notification ) -> void
    {
        auto* app = reinterpret_cast< NS::Application* >( notification->object() );
        app->setActivationPolicy( NS::ActivationPolicy::ActivationPolicyRegular );
    }

    auto Engine::AppDelegate::applicationDidFinishLaunching( NS::Notification* notification ) -> void
    {
        auto* app = reinterpret_cast< NS::Application* >( notification->object() );
        app->activateIgnoringOtherApps( true );
        Engine::get().initialize();
    }

    auto Engine::AppDelegate::applicationShouldTerminateAfterLastWindowClosed( NS::Application* ) -> bool
    {
        return true;
    }

    Engine::AppDelegate::~AppDelegate()
    {
        Engine::get().shutdown();
    }
}
