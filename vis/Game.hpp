#pragma once

#include "SceneManager.hpp"
#include <string>
#include "Common.hpp"

class Game : public Myapp::SceneBase
{
public:
    Game();

    void update() override;

    ~Game();
};

class TestScene : public Myapp::SceneBase
{
	void update() override;
};
