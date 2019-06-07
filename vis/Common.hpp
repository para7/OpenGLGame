#pragma once

#include "SceneManager.hpp"

struct Common
{
    unsigned mapsize;
};

using Myapp = Mysystem::SceneMaster <std::string, Common>;