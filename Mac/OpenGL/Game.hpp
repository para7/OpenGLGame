#pragma once

#include "SceneManager.hpp"
#include <string>
#include "Common.hpp"
#include "Inputs.hpp"
#include <iostream>
#include <vector>
#include "Utilities.hpp"
#include <random>
#include "StopWatch.hpp"

class Game : public Myapp::SceneBase
{
private:

    Utils::Point mapsize;
    std::random_device rd;
    std::mt19937 mt;

    float debug_eyelevel;

    StopWatch watch;

    std::vector<std::vector<int>> mapdata;

    Utils::Vec2 playerpos, lookpos;
    double ang;

    double chipsize;

    void Clustering();

    bool wallhack;
    StopWatch hacktime;

public:

    Game(Myapp* app);

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
