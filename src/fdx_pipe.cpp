#include "bn_sprite_items_pipe_sprites.h"
#include "bn_sprite_ptr.h"

#include "fdx_constants.h"
#include "fdx_pipe.h"

namespace fdx {
Pipe::Pipe() = default;

void Pipe::spawn(int sprite_index, int y_offset) {

    bn::sprite_ptr sprite_1 = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, y_offset - 72, sprite_index + 4); // Top cap
    sprite_1.set_z_order(2);

    bn::sprite_ptr sprite_2 = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, y_offset - 136, sprite_index); // Top body
    sprite_2.set_z_order(1);

    bn::sprite_ptr sprite_3 = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, y_offset + 56, sprite_index); // Bottom cap
    sprite_3.set_z_order(2);

    bn::sprite_ptr sprite_4 = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, y_offset + 120, sprite_index + 4); // Bottom body
    sprite_4.set_z_order(1);

    _sprites.push_back(sprite_1);
    _sprites.push_back(sprite_2);
    _sprites.push_back(sprite_3);
    _sprites.push_back(sprite_4);

    _active = true;
}

void Pipe::update() {
    if (!_active) {
        return;
    }

    // Reset pipe if sprites are off screen
    // Check using first sprite but this shows all sprites are off screen
    if (_sprites[0].x() <= ScreenLeftX - _sprites[0].shape_size().width()) {
        _sprites.clear();
        _active = false;
        return;
    }

    // If not off screen, move all sprites to the left
    for (bn::sprite_ptr &sprite : _sprites) {
        sprite.set_x(sprite.x() - 1);
    }
}

} // namespace fdx