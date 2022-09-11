#pragma once

#include "Key.hpp"
#include <functional>

namespace lava
{
    struct InputWrapper;

    class Input
    {
    public:
        Input();
        ~Input();
        
        auto isKeyPressed( Key ) -> bool;
        auto setOnMouseScroll( std::function<void(float, float)> ) -> void;
        auto setOnMouseMove( std::function<void(float, float)> ) -> void;

    private:
        InputWrapper* inputWrapper;
    };
}
