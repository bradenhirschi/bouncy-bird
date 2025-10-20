#pragma once

#include "bn_random.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_font.h"
#include "bn_sprite_ptr.h"
#include "bn_sram.h"
#include "fdx_game_state.h"
#include "fdx_ground_manager.h"

#include "bn_sprite_text_generator.h"
#include "bn_vector.h"
#include "fdx_pipe.h"
#include "fdx_player.h"

namespace fdx {

class MainState : public GameState {
  public:
    // Core
    MainState();
    ~MainState() override;
    GameState *update() override;

    // UI and text
    void display_menu_ui();
    void update_game_ui();
    void clear_ui();

  private:
    // Helper
    bn::random _random = bn::random();

    // Player
    bn::optional<fdx::Player> _player;
    void set_up_player();

    // Obstacles and backgrounds
    bn::array<fdx::Pipe, 6> _pipes;
    int _pipe_spawn_counter = 0;
    fdx::GroundManager ground_manager = fdx::GroundManager(_random);

    // Game logic
    int _points = 0;
    int _last_score = 0;
    int _high_score = 0;
    bool _game_started = false;

    // UI and text
    bn::optional<bn::sprite_font> _font;
    bn::optional<bn::sprite_text_generator> _text_generator;
    bn::vector<bn::sprite_ptr, 32> _ui_sprites;
    bn::optional<bn::regular_bg_ptr> _menu_background;
};

} // namespace fdx
