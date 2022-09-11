#include "Window.hpp"

#include <util/Util.hpp>

namespace lava
{
    Window::Window( CGRect frame )
    {
        auto parameters = NS::WindowStyleMaskClosable | NS::WindowStyleMaskTitled;
        window = NS::Window::alloc()->init( frame, parameters, NS::BackingStoreBuffered, false );
    }

    auto Window::setWindowView( MTK::View* view ) -> void
    {
        window->setContentView( view );
        window->setTitle( TO_NS_STRING( "Window" ) );
        window->makeKeyAndOrderFront( nullptr );
    }

    Window::~Window()
    {
        window->release();
    }
}
