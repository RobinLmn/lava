#pragma once

#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

namespace lava
{
    class Window final
    {
    public:
        Window( CGRect frame );
        ~Window();
        
    public:
        auto setWindowView( MTK::View* ) -> void;
        
    private:
        NS::Window* window;
    };
}
