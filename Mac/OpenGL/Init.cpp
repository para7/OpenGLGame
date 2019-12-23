#include "Init.hpp"
#include "SceneManager.hpp"
#include "Game.hpp"
#include "GLFuncs.hpp"
#include <memory>
#include <string>
#include "Inputs.hpp"
#include "TimeSystem.h"
#include "Title.h"
#include "Result.hpp"

void MyInit()
{
	auto app = std::make_shared<Myapp>();

	app->Add<Title>("title");
	app->Add<Game>("game");
    app->Add<Result>("result");

	PushSceneManager(app);
}