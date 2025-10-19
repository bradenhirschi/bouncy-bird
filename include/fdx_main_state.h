#pragma once

#include "fdx_game_state.h"
#include "fdx_ground_manager.h"
#include "bn_random.h"
#include "bn_sprite_font.h"
#include "bn_sprite_ptr.h"
#include "bn_sram.h"

#include "fdx_pipe.h"
#include "fdx_player.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"

namespace fdx {

class MainState : public GameState {
  public:
    MainState();
    ~MainState() override;

    GameState *update() override;
    void display_menu_ui();
    void clear_menu_ui();

  private:
    // Helper
    bn::random _random = bn::random();

    // Player
    bn::optional<fdx::Player> _player;

    // Obstacles and backgrounds
    bn::array<fdx::Pipe, 6> _pipes;
    int _pipe_spawn_counter = 0;
    fdx::GroundManager ground_manager = fdx::GroundManager(_random);

    // Game logic
    int _points = 0;
    int _last_score = 0;
    int _high_score = 0;
    bool _game_started = false;

    // Text
    bn::optional<bn::sprite_font> _font;
    bn::optional<bn::sprite_text_generator> _text_generator;
    bn::vector<bn::sprite_ptr, 32> _text_sprites;
};

} // namespace fdx
