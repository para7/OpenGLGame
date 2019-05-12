#include "Init.hpp"
#include "SceneManager.hpp"
#include "Game.hpp"
#include "GLFuncs.hpp"


void MyInit()
{
	Myapp app;

	app.Add<Game>("game");

}