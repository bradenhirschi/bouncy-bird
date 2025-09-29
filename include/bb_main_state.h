#pragma once

#include "bb_game_state.h"
#include "bn_random.h"
#include "bn_sprite_font.h"
#include "bn_sprite_ptr.h"

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
    void display_game_over_ui();

  private:
    // Player
    bn::optional<bb::Player> _player;

    // Obstacles and backgrounds
    bn::array<bb::Pipe, 6> _pipes;
    int _pipe_spawn_counter = 0;

    // Helper
    bn::random _random = bn::random();

    // Game logic
    int _points = 0;
    bool _game_over = false;

    // Text
    bn::optional<bn::sprite_font> _font;
    bn::optional<bn::sprite_text_generator> _text_generator;
    bn::optional<bn::vector<bn::sprite_ptr, 32>> _game_over_text_sprite;
};

} // namespace bb
