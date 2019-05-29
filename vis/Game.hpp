#pragma once

#include "SceneManager.hpp"
#include <string>
#include "Common.hpp"

#include "Inputs.hpp"
#include <iostream>
#include <array>
#include "Utilities.hpp"

constexpr Utils::Point mapsize(40, 40);

class Game : public Myapp::SceneBase
{
private:

    float debug_eyelevel;


    std::array<std::array<int, mapsize.x>, mapsize.y> mapdata;

    Utils::Vec2 playerpos, lookpos;
    double ang;

    double chipsize;

    void Clustering();

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
