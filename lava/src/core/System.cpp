#include "System.hpp"

namespace lava
{
    System::System( entt::registry* registry )
        : registry( registry )
    {
    }

    System::~System()
    {
    }

    auto System::begin() -> void
    {
    }

    auto System::update() -> void
    {
    }

    auto System::shutdown() -> void
    {
    }
}
