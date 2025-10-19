#pragma once

#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace fdx {
struct Pipe {
  public:
    Pipe();

    void spawn(int sprite_index, int y_offset);
    void update();

    bn::vector<bn::sprite_ptr, 4> _sprites;

    bool _active = false;
};
} // namespace fdx