#include "Init.hpp"
#include "SceneManager.hpp"
#include "Game.hpp"
#include "GLFuncs.hpp"
#include <memory>
#include <string>

void MyInit()
{
	std::shared_ptr<Myapp> app;

	app->Add<Game>("game");

	PushSceneManager(app);
}