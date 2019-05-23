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
