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
    /// �L�[�������ꂽ�Ƃ��ɌĂяo�����
    /// </summary>
    /// <remarks>
    /// �������A�t�@���N�V�����L�[������L�[��Special�ōs��
    /// </remarks>
    /// <param name="key">
    /// �L�[���
    /// </param>
    /// <param name="x">
    /// �}�E�X�J�[�\�����Wx
    /// </param>
    /// <param name="y">
    /// �}�E�X�J�[�\�����Wy
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