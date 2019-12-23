#include "Title.h"

#include "Inputs.hpp"
#include "Utilities.hpp"
#include "WindowInfo.h"

Title::Title(Myapp* app)
    : SceneBase(app)
{
}

Title::~Title() {}

void Title::update()
{
    if (Input::IsClicked('u'))
    {
        getCommon()->mapsize = 16;
        getCommon()->difficulty = Common::small;
        changeScene("game");
    }
    if (Input::IsClicked('i'))
    {
        getCommon()->mapsize = 26;
        getCommon()->difficulty = Common::medium;
        changeScene("game");
    }
    if (Input::IsClicked('o'))
    {
        getCommon()->mapsize = 60;
        getCommon()->difficulty = Common::large;
        changeScene("game");
    }
}

void Title::draw() const
{
    glColor3d(1.0, 1.0, 1.0);
    int y = 20;
    Utils::DrawString("how to play", 20, 20 + y);
    Utils::DrawString("W   : go ahead", 40, 50 + y);
    Utils::DrawString("A,D : turn", 40, 70 + y);
    Utils::DrawString("S   : back", 40, 90 + y);

    Utils::DrawString("H   : Wall Hack(only once)", 40, 120 + y);
    y += 30;

    Utils::DrawString("play start -> U or I or O", 20, 150 + y);
    Utils::DrawString("select stage size.", 60, 180 + y);
    y += 10;
    Utils::DrawString("u : 15 x 15 map", 40, 220 + y);
    Utils::DrawString("i : 25 x 25 map", 40, 240 + y);
    Utils::DrawString("o : 60 x 60 map", 40, 260 + y);
}