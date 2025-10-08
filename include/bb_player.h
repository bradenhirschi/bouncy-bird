#pragma once

#include "bb_pipe.h"
#include "bn_fixed_point_fwd.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_ptr.h"

namespace bb {

class Player {
  public:
    Player(bn::sprite_ptr sprite);

    void flap();
    void update_position();
    bool collides_with_pipe(bb::Pipe &pipe);

    bn::fixed_point _position;

  private:
    bn::sprite_ptr _sprite;

    // Movement + physics
    bn::fixed _delta_x; // change in x position this update cycle
    bn::fixed _delta_y; // change in y position this update cycle

    bn::optional<bn::sprite_animate_action<6>> _flap_animation;
};

} // namespace bb