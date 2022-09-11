#import "InputProxy.h"
#import "Input.hpp"

namespace lava
{
    struct InputWrapper
    {
        InputProxy* inputProxy;
    };
    
    Input::Input()
    {
        inputWrapper = new InputWrapper();
        inputWrapper->inputProxy = [[InputProxy alloc] init];
        
        inputWrapper->inputProxy.onMouseScroll = [](float, float){};
        inputWrapper->inputProxy.onMouseMove = [](float, float){};
        
        [inputWrapper->inputProxy initialize];
    }
    
    Input::~Input()
    {
        [inputWrapper->inputProxy release];
        delete inputWrapper;
    }

    auto Input::setOnMouseScroll( std::function<void(float, float)> callback ) -> void
    {
        inputWrapper->inputProxy.onMouseScroll = callback;
    }

    auto Input::setOnMouseMove( std::function<void(float, float)> callback ) -> void
    {
        inputWrapper->inputProxy.onMouseMove = callback;
    }

    auto Input::isKeyPressed( Key keyCode ) -> bool
    {
        switch (keyCode)
        {
        case Key::A:
            return [inputWrapper->inputProxy isKeyPressed: GCKeyCodeKeyA];
        case Key::W:
            return [inputWrapper->inputProxy isKeyPressed: GCKeyCodeKeyW];
        case Key::S:
            return [inputWrapper->inputProxy isKeyPressed: GCKeyCodeKeyS];
        case Key::D:
            return [inputWrapper->inputProxy isKeyPressed: GCKeyCodeKeyD];
        case Key::LShift:
            return [inputWrapper->inputProxy isKeyPressed: GCKeyCodeLeftShift];
        case Key::Space:
            return [inputWrapper->inputProxy isKeyPressed: GCKeyCodeSpacebar];
        }
    }
}
