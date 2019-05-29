#include "Init.hpp"
#include "SceneManager.hpp"
#include "Game.hpp"
#include "GLFuncs.hpp"
#include <memory>
#include <string>
#include "Inputs.hpp"
#include "TimeSystem.h"

void MyInit()
{
	auto app = std::make_shared<Myapp>();

	app->Add<Game>("game");
	//app->Add<TestScene>("next");

	PushSceneManager(app);
}