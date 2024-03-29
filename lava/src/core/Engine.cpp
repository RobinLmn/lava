#include "Engine.hpp"
#include <chrono>

namespace lava
{
    auto Engine::initialize() -> void
    {
        auto frame = (CGRect){ {100.0, 100.0}, {800, 800} };
        device = MTL::CreateSystemDefaultDevice();
        auto mtkView = MTK::View::alloc()->init( frame, device );
        
        input = new Input();
        
        window = new Window( frame );
        world = new World();
        view = new View( mtkView, device, world );
        
        
        window->setWindowView( mtkView );
        world->begin();
        mtkView->setDelegate( view );
    }

    auto Engine::run() -> void
    {
        AppDelegate delegate;
        
        auto* autoReleasePool = NS::AutoreleasePool::alloc()->init();
        auto* app = NS::Application::sharedApplication();
        
        clock = new std::chrono::high_resolution_clock();
        lastTime = clock->now();
        
        app->setDelegate( &delegate );
        app->run();

        autoReleasePool->release();
    }

    auto Engine::update() -> void
    {
        using seconds = std::chrono::duration<double, std::ratio<1>>;
        const auto deltaTime = std::chrono::duration_cast<seconds>(clock->now() - lastTime).count();
        lastTime = clock->now();
        
        world->update( deltaTime );
    }

    auto Engine::get() -> Engine&
    {
        static Engine engine;
        return engine;
    }

    auto Engine::getDevice() -> MTL::Device*
    {
        return Engine::get().device;
    }

    auto Engine::isKeyPressed( Key key ) -> bool
    {
        return Engine::get().input->isKeyPressed( key );
    }

    auto Engine::setOnMouseScroll( std::function<void(float, float)> callback ) -> void
    {
        Engine::get().input->setOnMouseScroll( callback );
    }
    auto Engine::setOnMouseMove( std::function<void(float, float)> callback) -> void
    {
        Engine::get().input->setOnMouseMove( callback );
    }

    auto Engine::shutdown() -> void
    {
        world->end();
        device->release();
        
        delete input;
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
