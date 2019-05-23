#pragma once

#include "SceneManager.hpp"
#include <string>
#include "Common.hpp"

#include "Inputs.hpp"
#include <iostream>

class Game : public Myapp::SceneBase
{
public:
    Game();

    void update() override;

    ~Game();
};

class TestScene : public Myapp::SceneBase
{
    void update() override
    {
        //        std::cout << "Second Scene" << std::endl;

        if (Input::IsClicked('a'))
        {
            std::cout << "aaaaaaaa" << std::endl;
        }
        if (Input::IsPressed('b'))
        {
            std::cout << "b" << std::endl;
        }
    }
};
