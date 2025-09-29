#include "bb_game_state.h"
#include "bn_random.h"
#include "bn_sprite_font.h"
#include "bn_sprite_items_common_variable_8x16_font.h"
#include "bn_sprite_items_player_sprite.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "bb_main_state.h"
#include "bb_pipe.h"
#include "bb_player.h"
#include "bn_string_view.h"

namespace bb {

MainState::MainState() {
    // Set up player
    bn::sprite_ptr player_sprite = bn::sprite_items::player_sprite.create_sprite(0, 0);
    _player = bb::Player(player_sprite);
}

MainState::~MainState() {}

GameState *MainState::update() {
    if (!_game_over) {

        // Spawn a pipe every 90 frames
        if (_pipe_spawn_counter >= 90) {
            for (auto &pipe : _pipes) {
                if (!pipe._active) {
                    int random_int = _random.get_unbiased_int(4);

                    pipe.spawn(random_int);
                    pipe._active = true;
                    _pipe_spawn_counter = 0;
                    break;
                }
            }
        }
        _pipe_spawn_counter++;

        // Move all existing pipes
        for (auto &pipe : _pipes) {
            pipe.update();

            if (pipe._active && _player->collides_with_pipe(pipe)) {
                pipe._active = false;
                pipe._sprite.reset();
                _game_over = true;
            }
        }

        // Update player
        _player->update_position();
    } else {
        display_game_over_ui();
    }

    return nullptr;
}

void MainState::display_game_over_ui() {
    bn::string_view text = bn::string_view("Game Over");

    _font = bn::sprite_font(bn::sprite_items::common_variable_8x16_font);
    _text_generator = bn::sprite_text_generator(_font.value());
    _game_over_text_sprite = _text_generator->generate<32>(0, 0, text);
}

} // namespace bb