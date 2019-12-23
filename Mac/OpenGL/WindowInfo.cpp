#include "WindowInfo.h"

namespace Window
{
    static Utils::Point size;

    void SetWindowSize(int w, int h)
    {
        size.x = w;
        size.y = h;
    }

    Utils::Point GetWindowSize()
    {
        return size;
    }
}  // namespace Window