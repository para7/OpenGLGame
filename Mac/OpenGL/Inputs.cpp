#include "Inputs.hpp"
#include <unordered_map>
#include <array>

#include <iostream>

namespace Input
{
    std::array<int, 256> inputraw, inputstatus;


    void Init()
    {
        for (auto& i : inputraw)
        {
            i = 0;
        }
    }

    /// <summary>
    /// キーが押されたときに呼び出される
    /// </summary>
    /// <remarks>
    /// ただし、ファンクションキーや方向キーはSpecialで行う
    /// </remarks>
    /// <param name="key">
    /// キー情報
    /// </param>
    /// <param name="x">
    /// マウスカーソル座標x
    /// </param>
    /// <param name="y">
    /// マウスカーソル座標y
    /// </param>
    void InputKbd(unsigned char key, int x, int y)
    {
        inputraw[key] = 1;
    }

    void ReleaseKbd(unsigned char key, int x, int y)
    {
        inputraw[key] = 0;
    }

    int GetInput(unsigned char key)
    {
        return inputstatus[key];
    }

    bool IsPressed(unsigned char key)
    {
        return 0 < inputstatus[key] ;
    }

    bool IsClicked(unsigned char key)
    {
        return inputstatus[key] == 1;
    }


    void Update()
    {
        for (int i = 0; i < inputraw.size(); ++i)
        {
            inputstatus[i] = inputraw[i] == 0 ? 0 : inputstatus[i] + 1;
        }


        if (0 < inputraw[KeyKind::Esc])
        {
            exit(0);
        }
    }
}