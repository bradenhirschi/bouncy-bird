#include "bb_constants.h"
#include "bb_hitbox.h"
#include "bn_fixed_rect.h"
#include "bn_fixed_rect_fwd.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_shape_size.h"

#include "bb_player.h"

namespace bb {

const bn::fixed gravity = 0.2;
const bn::fixed flap_strength = 4;
const bn::fixed max_delta_y = 3;

Player::Player(bn::sprite_ptr sprite) : _sprite(sprite), _position(sprite.position()) {}

void Player::flap() {
    // Set delta y to -flap strength instead of just subtracting it
    // This lets the jump height always be the same regardless of current
    // downward velocity
    _delta_y = -flap_strength;
};

bool Player::collides_with_pipe(bb::Pipe &pipe) {
    bn::fixed_rect player_hitbox = bn::fixed_rect(_position.x(), _position.y(), 24, 24);

    bn::fixed_rect pipe_top_hitbox = bn::fixed_rect(pipe._sprite_top->x(), pipe._sprite_top->y(),
                                                    pipe._sprite_top->shape_size().width(),
                                                    pipe._sprite_top->shape_size().height());

    bn::fixed_rect pipe_bottom_hitbox = bn::fixed_rect(
        pipe._sprite_bottom->x(), pipe._sprite_bottom->y(),
        pipe._sprite_bottom->shape_size().width(), pipe._sprite_bottom->shape_size().height());

    if (player_hitbox.intersects(pipe_top_hitbox) || player_hitbox.intersects(pipe_bottom_hitbox)) {
        return true;
    }
    return false;
};

void Player::update_position() {
    // Flap
    if (bn::keypad::a_pressed()) {
        flap();
    }

    // Apply gravity
    _delta_y += gravity;

    // Clamp maximum fall speed
    if (_delta_y > max_delta_y) {
        _delta_y = max_delta_y;
    }

    // Update internal position
    _position.set_y(_sprite.y() + _delta_y);

    // Ensure that position stays within the screen
    int half_sprite_height = _sprite.shape_size().height() / 2;

    if (_position.y() < bb::ScreenTopY + half_sprite_height) {
        _position.set_y(bb::ScreenTopY + half_sprite_height);
    } else if (_position.y() > bb::ScreenBottomY - half_sprite_height) {
        _position.set_y(bb::ScreenBottomY - half_sprite_height);
        _delta_y = 0;
    }

    // Update actual sprite position based on calculated deltas
    _sprite.set_y(_position.y());
};

} // namespace bb