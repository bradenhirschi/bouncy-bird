#include "bn_fixed_rect.h"
#include "bn_fixed_rect_fwd.h"
#include "bn_keypad.h"
#include "bn_sprite_item.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_shape_size.h"

#include "bn_sprite_animate_actions.h"
#include "bn_sprite_items_bird_sprites.h"
#include "fdx_constants.h"
#include "fdx_player.h"

namespace fdx {

const bn::fixed gravity = 0.225;
const bn::fixed flap_strength = 4;
const bn::fixed max_delta_y = 3;

Player::Player(bn::sprite_ptr sprite) : _position(sprite.position()), _sprite(sprite) {}

void Player::flap() {
    // Set delta y to -flap strength instead of just subtracting it
    // This lets the jump height always be the same regardless of current
    // downward velocity
    _delta_y = -flap_strength;

    // Play a new flap animation
    _flap_animation = bn::create_sprite_animate_action_once(
        _sprite, 10, bn::sprite_items::bird_sprites.tiles_item(), 0, 1, 2, 3, 1, 0);
};

bool Player::collides_with_pipe(fdx::Pipe &pipe) {
    bn::fixed_rect player_hitbox = bn::fixed_rect(_position.x(), _position.y(), 16, 14);

    for (bn::sprite_ptr &sprite : pipe._sprites) {
        bn::fixed_rect pipe_sprite_hitbox = bn::fixed_rect(
            sprite.x(), sprite.y(), sprite.shape_size().width(), sprite.shape_size().height());

        if (player_hitbox.intersects(pipe_sprite_hitbox)) {
            return true;
        }
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

    if (_position.y() < fdx::ScreenTopY + half_sprite_height) {
        _position.set_y(fdx::ScreenTopY + half_sprite_height);
    } else if (_position.y() > fdx::ScreenBottomY - half_sprite_height) {
        _position.set_y(fdx::ScreenBottomY - half_sprite_height);
        _delta_y = 0;
    }

    // Update actual sprite position based on calculated deltas
    _sprite.set_y(_position.y());

    // Update flap animation if it's active
    if (_flap_animation) {
        _flap_animation->update();

        // Once finished, clear it
        if (_flap_animation->done()) {
            _flap_animation.reset();
        }
    }
};

} // namespace fdx