#pragma once

#include "GLincludes.h"

class GLEnableScope
{
private:

    const GLenum _mode;

public:

    explicit GLEnableScope(GLenum mode)
        : _mode(mode)
    {
        glEnable(_mode);
    }

    virtual ~GLEnableScope() final
    {
        glDisable(_mode);
    }
};