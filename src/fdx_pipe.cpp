#include "bn_sprite_items_pipe_sprites.h"
#include "bn_sprite_ptr.h"

#include "fdx_constants.h"
#include "fdx_pipe.h"

namespace fdx {
Pipe::Pipe() = default;

void Pipe::spawn(int sprite_index, int y_offset) {

    _sprite_top = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, ScreenTopY + 5 + y_offset, sprite_index);
    _sprite_top->set_z_order(1);

    _sprite_bottom = bn::sprite_items::pipe_sprites.create_sprite(
        ScreenRightX, ScreenBottomY - 15 + y_offset, sprite_index);
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

} // namespace fdx