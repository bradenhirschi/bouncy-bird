#pragma once

namespace fdx {

class GameState {
  public:
    GameState() = default;
    virtual ~GameState() = default;

    virtual GameState *update();

  private:
};

} // namespace fdx