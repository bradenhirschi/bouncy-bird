#include "bn_sprite_items_pipe_sprites.h"
#include "bn_sprite_ptr.h"

#include "bb_constants.h"
#include "bb_pipe.h"

namespace bb {
Pipe::Pipe() = default;

void Pipe::spawn(int sprite_index, int y_offset) {

    _sprite_top = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, ScreenTopY + 10 + y_offset, sprite_index);
    _sprite_top->set_z_order(1);

    _sprite_bottom = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, ScreenBottomY - 26 + y_offset, sprite_index);
    _sprite_bottom->set_z_order(1);

    _active = true;
}

void Pipe::update() {
    if (!_active || !_sprite_top || !_sprite_bottom) {
        return;
    }

    // Check using _sprite_top but this shows both sprites are off screen
    if (_sprite_top->x() <= ScreenLeftX - _sprite_top->shape_size().width()) {
        _sprite_top.reset();
        _sprite_bottom.reset();
        _active = false;
        return;
    }

    _sprite_top->set_x(_sprite_top->x() - 1);
    _sprite_bottom->set_x(_sprite_bottom->x() - 1);
}

} // namespace bb