#pragma once

#include "SceneManager.hpp"
#include <string>

class Game : public Mysystem::SceneMaster<std::string>::SceneBase
{
public:
    Game();

    void update() override;

    ~Game();
};

