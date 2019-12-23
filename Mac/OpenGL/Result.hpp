#pragma once

#include "Common.hpp"
#include "Inputs.hpp"
#include <string>
#include "DrawString.hpp"

class Result : public Myapp::SceneBase
{
private:

    std::string timestr;

public:
    Result(Myapp* app):SceneBase(app)
    {        
        timestr = std::to_string(getCommon()->time);

        glColor3f(1.0,1.0,1.0);
    }

    void update() override
    {
        if (Input::IsClicked('w'))
        {
            changeScene("title");
        }
    }

    void draw()const override
    {
        Utils::DrawString("Clear time", 20, 20);
        Utils::DrawString(timestr.c_str(), 25, 40);
        Utils::DrawString("Best time", 20, 70);
        Utils::DrawString(std::to_string(getCommon()->sbest), 25, 90);
        Utils::DrawString(std::to_string(getCommon()->mbest), 25, 110);
        Utils::DrawString(std::to_string(getCommon()->lbest), 25, 130);

        Utils::DrawString("please press W key.", 20, 170);
    }
};