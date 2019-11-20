#pragma once

#include <string>
#include "Vec23.hpp"
#include "GLincludes.h"
#include "WindowInfo.h"

namespace Utils
{

    //http://slis.tsukuba.ac.jp/~fujisawa.makoto.fu/lecture/iml/text/screen_character.html
    void DrawString(std::string str, int x0, int y0);

}