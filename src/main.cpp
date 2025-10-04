#include "bn_core.h"
#include "bn_regular_bg_items_background.h"
#include "bn_regular_bg_ptr.h"
#include "bn_unique_ptr.h"

#include "bb_game_state.h"
#include "bb_main_state.h"

int main() {
    bn::core::init();

    // Draw background which is the same for all game states
    bn::regular_bg_ptr background = bn::regular_bg_items::background.create_bg(0, 0);

    // Initialize game state
    bn::unique_ptr<bb::GameState> current_state = bn::make_unique<bb::MainState>();

    while (true) {
        bb::GameState *next_state = current_state->update();

        // Switch states if needed
        if (next_state != nullptr) {
            current_state.reset(next_state);
        }

        bn::core::update();
    }
}