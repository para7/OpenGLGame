#pragma once

#include "Common.hpp"

class Title : public Myapp::SceneBase
{
public:
    Title();
    ~Title();

    void update() override;
    void draw() const override;
};

