#pragma once

namespace Input
{
    // esc27 del127 enter13 space32
    enum KeyKind
    {
        Enter = 13,
        Esc = 27,
        Space = 32,
        Del = 127
    };

    void Init();

    void InputKbd(unsigned char key, int x, int y);

    void ReleaseKbd(unsigned char key, int x, int y);

    int GetInput(unsigned char key);

    bool IsPressed(unsigned char key);

    bool IsClicked(unsigned char key);

    void Update();
}  // namespace Input
