#include "bn_core.h"
#include "bn_unique_ptr.h"

#include "bb_game_state.h"
#include "bb_main_state.h"

int main() {
    bn::core::init();

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