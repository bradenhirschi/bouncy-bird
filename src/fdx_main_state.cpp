#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_random.h"
#include "bn_regular_bg_items_menu_background.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_font.h"
#include "bn_sprite_items_bird_sprites.h"
#include "bn_sprite_items_common_variable_8x16_font.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_sram.h"
#include "bn_string.h"
#include "bn_string_view.h"

#include "fdx_constants.h"
#include "fdx_game_state.h"
#include "fdx_main_state.h"
#include "fdx_pipe.h"
#include "fdx_player.h"

namespace fdx {

struct SaveData {
    int high_score = 0;
    int last_score = 0;
};

MainState::MainState() {
    // Set up text generator
    _font = bn::sprite_font(bn::sprite_items::common_variable_8x16_font);
    _text_generator = bn::sprite_text_generator(_font.value());
    _text_generator->set_center_alignment();

    // Advance the random number generator to fake non-deterministic randomness
    int frames = bn::core::current_cpu_ticks(); // Something pretty random
    for (int i = 0; i < frames % 100; ++i) {
        _random.update(); // Update _random's current internal state
    }

    // Read high score from sram
    SaveData data;
    bn::sram::read(data);

    _high_score = data.high_score;
    _last_score = data.last_score;

    // Display menu ui when the game starts
    display_menu_ui();
}

MainState::~MainState() {}

GameState *MainState::update() {
    // // Spawn ground background tiles every frame
    ground_manager.update();

    if (_game_started) {
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
            if (pipe._active && pipe._sprites[0].x() == PlayerX) {
                _points++;
            }

            // Game over if player collides with pipe
            if (pipe._active && _player->collides_with_pipe(pipe)) {
                // Write save data
                SaveData data;
                data.last_score = _points;
                data.high_score = _points > _high_score ? _points : _high_score;
                bn::sram::write(data);

                // Restart game
                return new MainState();
            }
        }

        // Game over if player touches ground
        if (_player->_position.y() > ScreenBottomY - 16) {
            // Write save data
            SaveData data;
            data.last_score = _points;
            data.high_score = _points > _high_score ? _points : _high_score;
            bn::sram::write(data);

            // Restart game
            return new MainState();
        }

        // Update player
        _player->update_position();

        // Update game UI
        update_game_ui();
    } else {
        if (bn::keypad::start_pressed()) {
            // set up bird
            set_up_player();
            _game_started = true;
            clear_ui();
        }
    }

    return nullptr;
}

void MainState::set_up_player() {
    // Set up player
    bn::sprite_ptr player_sprite =
        bn::sprite_items::bird_sprites.create_sprite(PlayerX, PlayerStartY, 0);
    _player = fdx::Player(player_sprite);
}

void MainState::update_game_ui() {
    clear_ui();
    _text_generator->generate(0, -50, bn::to_string<10>(_points), _ui_sprites);
}

void MainState::display_menu_ui() {
    // Menu background
    _menu_background = bn::regular_bg_items::menu_background.create_bg(0, 0);

    // Score text
    _text_generator->set_right_alignment();
    _text_generator->generate(52, -21, bn::to_string<4>(_last_score), _ui_sprites);
    _text_generator->generate(52, 7, bn::to_string<4>(_high_score), _ui_sprites);

    // Chosen bird
    bn::sprite_ptr bird_sprite =
        bn::sprite_items::bird_sprites.create_sprite(PlayerX, PlayerStartY, 0);
    _ui_sprites.push_back(bird_sprite);
}

void MainState::clear_ui() {
    // Clear text sprites and menu background
    _ui_sprites.clear();
    _menu_background.reset();

    // Set center alignment for score in gameplay ui. This will be overwritten in menu ui
    _text_generator->set_center_alignment();
}

} // namespace fdx