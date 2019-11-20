#pragma once

#include "Common.hpp"

class Title : public Myapp::SceneBase
{
public:
    Title(Myapp* app);
    ~Title();

    void update() override;
    void draw() const override;
};

