#pragma once

#include "bn_fixed_point_fwd.h"
#include "bn_sprite_animate_actions.h"
#include "bn_sprite_ptr.h"

#include "fdx_pipe.h"

namespace fdx {

class Player {
  public:
    Player(bn::sprite_ptr sprite);

    void flap();
    void update_position();
    bool collides_with_pipe(fdx::Pipe &pipe);

    bn::fixed_point _position;

  private:
    // Graphics and animation
    bn::sprite_ptr _sprite;
    bn::optional<bn::sprite_animate_action<6>> _flap_animation;

    // Movement and physics
    bn::fixed _delta_y; // change in y position this update cycle
};

} // namespace fdx