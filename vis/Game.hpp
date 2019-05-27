#pragma once

#include "SceneManager.hpp"
#include <string>
#include "Common.hpp"

#include "Inputs.hpp"
#include <iostream>
#include <array>


class Game : public Myapp::SceneBase
{

private:

    std::array<std::array<int, 10>, 10> mapdata;

public:

    Game();

    void update() override;

    void draw() const override;

    ~Game();
};

//class TestScene : public Myapp::SceneBase
//{
//    void update() override
//    {
//        //        std::cout << "Second Scene" << std::endl;
//
//        if (Input::IsClicked('a'))
//        {
//            std::cout << "aaaaaaaa" << std::endl;
//        }
//        if (Input::IsPressed('b'))
//        {
//            std::cout << "b" << std::endl;
//        }
//    }
//
//    void draw() const
//    {
//
//    }
//};
