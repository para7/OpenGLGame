#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "Common.hpp"
#include "Inputs.hpp"
#include "SceneManager.hpp"
#include "StopWatch.hpp"
#include "Utilities.hpp"
#include "bmptest.h"

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

    enum MapInfo
    {
        Wall = 0,
        Floor = 1,
        Goal = 2,
        Walked = 10
    };
    
//    testBMP wallbmp;

public:
    Game(Myapp* app);

    void update() override;

    void draw() const override;

    ~Game();
};

// class TestScene : public Myapp::SceneBase
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
