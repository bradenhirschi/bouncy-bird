#include "bb_constants.h"
#include "bn_sprite_items_ground_sprites.h"

#include "bb_ground_manager.h"

namespace bb {

GroundManager::GroundManager(bn::random _random) {
    int x = ScreenLeftX;
    for (int i = 0; i < tile_count; i++) {
        int random_int_for_tile = _random.get_unbiased_int(0, 4);
        _tiles.push_back(
            bn::sprite_items::ground_sprites.create_sprite(x, ground_y, random_int_for_tile));
        x += tile_width;
    }
};

void GroundManager::update() {
    for (auto &sprite : _tiles) {
        sprite.set_x(sprite.x() - scroll_speed);

        // if it moved off screen, wrap around:
        if (sprite.x() < ScreenLeftX - tile_width) {
            sprite.set_x(sprite.x() + total_scroll_width);
            sprite.set_tiles(bn::sprite_items::ground_sprites.tiles_item(), _random.get_int(4));
        }
    }
};
} // namespace bb