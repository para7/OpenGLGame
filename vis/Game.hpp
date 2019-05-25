#pragma once

#include "SceneManager.hpp"
#include <string>
#include "Common.hpp"

#include "Inputs.hpp"
#include <iostream>
#include <array>

struct Vec2
{
    int x, y;

    Vec2() : x(0), y (0) {};

    Vec2(int _x, int _y)
        : x(_x)
        , y(_y)
    {}
};

class Game : public Myapp::SceneBase
{

private:

    std::array<std::array<int, 10>, 10> mapdata;

    Vec2 pos;

public:

    Game();

    void update() override;

    void draw() const override;

    ~Game() {};
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

    void draw() const
    {

    }
};
