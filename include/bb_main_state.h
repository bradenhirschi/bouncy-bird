#pragma once

#include "bb_game_state.h"
#include "bb_ground_manager.h"
#include "bn_random.h"
#include "bn_sprite_font.h"
#include "bn_sprite_ptr.h"
#include "bn_sram.h"

#include "bb_pipe.h"
#include "bb_player.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"

namespace bb {

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
    bn::optional<bb::Player> _player;

    // Obstacles and backgrounds
    bn::array<bb::Pipe, 6> _pipes;
    int _pipe_spawn_counter = 0;
    bb::GroundManager ground_manager = bb::GroundManager(_random);

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

} // namespace bb
