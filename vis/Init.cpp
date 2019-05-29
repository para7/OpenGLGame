#include "Init.hpp"
#include "SceneManager.hpp"
#include "Game.hpp"
#include "GLFuncs.hpp"
#include <memory>
#include <string>
#include "Inputs.hpp"
#include "TimeSystem.h"
#include "Title.h"

void MyInit()
{
	auto app = std::make_shared<Myapp>();

	app->Add<Title>("title");
	app->Add<Game>("game");

	PushSceneManager(app);
}