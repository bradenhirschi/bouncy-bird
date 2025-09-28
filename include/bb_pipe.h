#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"

namespace bb {
struct Pipe {
  public:
    Pipe();

    void spawn(int sprite_index);
    void update();

    bn::optional<bn::sprite_ptr> _sprite;
    bool _active = false;
};
} // namespace bb