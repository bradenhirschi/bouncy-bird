#include "bn_sprite_items_pipe_sprites.h"
#include "bn_sprite_ptr.h"

#include "bb_constants.h"
#include "bb_pipe.h"

namespace bb {
Pipe::Pipe() = default;

void Pipe::spawn(int sprite_index) {
    int spawn_y = ScreenBottomY - bn::sprite_items::pipe_sprites.shape_size().height() / 2;
    _sprite = bn::sprite_items::pipe_sprites.create_sprite(ScreenRightX, spawn_y, sprite_index);

    _active = true;
}

void Pipe::update() {
    if (!_active || !_sprite) {
        return;
    }

    if (_sprite->x() <= ScreenLeftX - _sprite->shape_size().width()) {
        _sprite.reset();
        _active = false;
        return;
    }

    _sprite->set_x(_sprite->x() - 1);
}

} // namespace bb