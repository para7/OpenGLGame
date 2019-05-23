#include "Game.hpp"

#include <iostream>

Game::Game()
{
}

void Game::update()
{
    std::cout << "First Scene" << std::endl;

	changeScene("next");
}


Game::~Game()
{
}

void TestScene::update()
{
	std::cout << "Second Scene" << std::endl;
}