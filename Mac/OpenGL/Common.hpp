#pragma once

#include "SceneManager.hpp"

struct Common
{
    unsigned mapsize;

    double time;

    double sbest, mbest, lbest;

    Common()
    {
        sbest = mbest = lbest = 999999.999999;
    }

    enum Difficulty
    {
        small,
        medium,
        large
    } difficulty;
};

using Myapp = Mysystem::SceneMaster<std::string, Common>;