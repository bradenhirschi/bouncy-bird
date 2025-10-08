#pragma once

#include "bb_constants.h"
#include "bn_random.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_vector.h"

namespace bb {
class GroundManager {
  public:
    GroundManager(bn::random _random);
    void update();

  private:
    static constexpr int tile_width = 16;
    static constexpr int tile_height = 16;
    static constexpr int ground_y = ScreenBottomY - (tile_height / 2);
    static constexpr int scroll_speed = 1;
    static constexpr int tile_count = (ScreenWidth / tile_width) + 2;
    static constexpr int total_scroll_width = tile_width * tile_count;

    bn::vector<bn::sprite_ptr, tile_count> _tiles;
    bn::random _random;
};
} // namespace bb