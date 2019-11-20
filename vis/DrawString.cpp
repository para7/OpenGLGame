#include "DrawString.hpp"

namespace Utils
{

    //http://slis.tsukuba.ac.jp/~fujisawa.makoto.fu/lecture/iml/text/screen_character.html
    void DrawString(std::string str, int x0, int y0)
    {
        //auto winsize = Window::GetWindowSize();

        auto winsize = Window::GetWindowSize();

        glDisable(GL_LIGHTING);
        // ���s���e�ɂ���
        glMatrixMode(GL_PROJECTION);
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0, winsize.x, winsize.y, 0);
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glLoadIdentity();

        // ��ʏ�Ƀe�L�X�g�`��
        glRasterPos2f(x0, y0);
        int size = (int)str.size();
        for (int i = 0; i < size; ++i)
        {
            char ic = str[i];
            glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic);
        }

        glPopMatrix();
        glMatrixMode(GL_PROJECTION);
        glPopMatrix();
        glMatrixMode(GL_MODELVIEW);
    }

}