#include "Title.h"

#include "Inputs.hpp"
#include "Utilities.hpp"
#include "WindowInfo.h"

Title::Title()
{
}


Title::~Title()
{
}

void Title::update()
{
    if (Input::IsClicked('a') || Input::IsClicked('b') || Input::IsClicked('c'))
    {
        changeScene("game");
    }
}


void Title::draw() const
{
    glColor3d(1.0, 1.0, 1.0);
    auto size = Window::GetWindowSize();
    int y = 20;
    Utils::DrawString("how to play", size.x, size.y, 20, 20 + y);
    Utils::DrawString("W : go ahead", size.x, size.y, 40, 50 + y);
    Utils::DrawString("S : back", size.x, size.y, 40, 90 + y);
    Utils::DrawString("A,D : turn", size.x, size.y, 40, 70 + y);
    Utils::DrawString("play start -> A or B or C", size.x, size.y, 20, 150 + y);
    Utils::DrawString("select stage size.", size.x, size.y, 60, 180 + y);
    y += 10;
    Utils::DrawString("a : 20 x 20 map", size.x, size.y, 40, 220 + y);
    Utils::DrawString("b : 40 x 40 map", size.x, size.y, 40, 240 + y);
    Utils::DrawString("c : 60 x 60 map", size.x, size.y, 40, 260 + y);
}