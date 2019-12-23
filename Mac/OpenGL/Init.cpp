#include "Init.hpp"
#include <memory>
#include <string>
#include "GLFuncs.hpp"
#include "Game.hpp"
#include "Inputs.hpp"
#include "Result.hpp"
#include "SceneManager.hpp"
#include "TimeSystem.h"
#include "Title.h"

void MyInit()
{
    auto app = std::make_shared<Myapp>();

    app->Add<Title>("title");
    app->Add<Game>("game");
    app->Add<Result>("result");

    PushSceneManager(app);
}