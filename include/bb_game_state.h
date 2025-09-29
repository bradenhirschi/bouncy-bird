#pragma once

namespace bb {

class GameState {
  public:
    GameState() = default;
    virtual ~GameState() = default;

    virtual GameState *update();

  private:
};

} // namespace bb