#include "bb_pipe.h"
#include "bn_core.h"
#include "bn_random.h"
#include "bn_sprite_items_player_sprite.h"
#include "bn_sprite_ptr.h"

#include "bb_player.h"

int main() {
    bn::core::init();

    // Set up player
    bn::sprite_ptr player_sprite = bn::sprite_items::player_sprite.create_sprite(0, 0);
    bb::Player player = bb::Player(player_sprite);

    // Set up pipes
    bn::array<bb::Pipe, 6> pipes;
    int pipe_spawn_counter = 0;

    // Helper classes
    bn::random random = bn::random();

    // Main update loop
    while (true) {

        // Spawn a pipe every 90 frames
        if (pipe_spawn_counter >= 90) {
            for (auto &pipe : pipes) {
                if (!pipe._active) {
                    int random_int = random.get_unbiased_int(4);

                    pipe.spawn(random_int);
                    pipe._active = true;
                    pipe_spawn_counter = 0;
                    break;
                }
            }
        }
        pipe_spawn_counter++;

        // Move all existing pipes
        for (auto &pipe : pipes) {
            pipe.update();

            if (pipe._active && player.collides_with_pipe(pipe)) {
                pipe._active = false;
                pipe._sprite.reset();
            }
        }

        // Update player
        player.update_position();

        // Finish update
        bn::core::update();
    }
}