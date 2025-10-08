#include "bb_constants.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_sprite_font.h"
#include "bn_sprite_items_bird_sprites.h"
#include "bn_sprite_items_common_variable_8x16_font.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"

#include "bb_game_state.h"
#include "bb_main_state.h"
#include "bb_pipe.h"
#include "bb_player.h"
#include "bn_string.h"
#include "bn_string_view.h"

namespace bb {

MainState::MainState() {
    // Set up player
    bn::sprite_ptr player_sprite = bn::sprite_items::bird_sprites.create_sprite(-40, 0, 0);
    _player = bb::Player(player_sprite);

    // Advance the random number generator to fake non-deterministic randomness
    int frames = bn::core::current_cpu_ticks(); // Something pretty random
    for (int i = 0; i < frames % 100; ++i) {
        _random.update(); // Update _random's current internal state
    }
}

MainState::~MainState() {}

GameState *MainState::update() {
    if (!_game_over) {

        // // Spawn ground background tiles every frame
        ground_manager.update();

        // Spawn a pipe every 120 frames
        if (_pipe_spawn_counter == 120) {
            for (auto &pipe : _pipes) {
                if (!pipe._active) {
                    int random_int_for_color = _random.get_unbiased_int(4);
                    int random_int_for_y_offset = _random.get_unbiased_int(-6, 6) * 5;

                    pipe.spawn(random_int_for_color, random_int_for_y_offset);
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

            // We're checking just the pipe's top sprite but this shows the player passed top +
            // bottom
            if (pipe._active && pipe._sprite_top->x() == -40) {
                _points++;
            }

            // Game over if player collides with pipe
            if (pipe._active && _player->collides_with_pipe(pipe)) {
                _game_over = true;
                display_game_over_ui();
            }
        }

        // Game over if player touches ground
        if (_player->_position.y() > ScreenBottomY - 32) {
            _game_over = true;
            display_game_over_ui();
        }

        // Update player
        _player->update_position();
    } else {
        if (bn::keypad::start_pressed()) {
            return new MainState();
        }
    }

    return nullptr;
}

void MainState::display_game_over_ui() {
    _font = bn::sprite_font(bn::sprite_items::common_variable_8x16_font);

    _text_generator = bn::sprite_text_generator(_font.value());
    _text_generator->set_center_alignment();

    _text_generator->generate(0, 0, "Score", _text_sprites);
    _text_generator->generate(0, 10, bn::to_string<10>(_points), _text_sprites);
    _text_generator->generate(0, 20, "Best", _text_sprites);
    _text_generator->generate(0, 30, bn::to_string<10>(_points), _text_sprites);
}

} // namespace bb