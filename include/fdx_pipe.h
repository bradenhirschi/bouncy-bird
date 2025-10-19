#pragma once

#include "bn_optional.h"
#include "bn_sprite_ptr.h"

namespace fdx {
struct Pipe {
  public:
    Pipe();

    void spawn(int sprite_index, int y_offset);
    void update();

    bn::optional<bn::sprite_ptr> _sprite_top;
    bn::optional<bn::sprite_ptr> _sprite_bottom;

    bool _active = false;
};
} // namespace fdx