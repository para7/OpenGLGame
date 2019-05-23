// g1772011
// �Έ�Y��
//

#include "GLFuncs.hpp"
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "Init.hpp"
#include "Inputs.hpp"

int main(int argc, char *argv[])
{
    //��ԍŏ���OpenGL�̏�����
    glutInit(&argc, argv);

    //�����̏������֐�
    glInits(argv[0]);
	MyInit();

    //�`����s���֐���ݒ�
    glutDisplayFunc(display);

    //�L�[�{�[�h�̓��͂���������֐���ݒ�
    glutKeyboardFunc(Input::InputKbd);

    glutKeyboardUpFunc(Input::ReleaseKbd);

    //�t�@���N�V�����L�[�A���L�[�̓��͂���������֐���ݒ�
    glutSpecialFunc(mySkey);

    //�}�E�X�̃N���b�N����������֐���ݒ�
    glutMouseFunc(myMouse);

    //�}�E�X�̃h���b�O����������֐���ݒ�
    glutMotionFunc(myMotion);

    //�E�B���h�E�̃T�C�Y���ύX���ꂽ�Ƃ��ɏ�������֐���ݒ�
    glutReshapeFunc(myReshape);

    //���쒆�J��Ԃ��Ăяo�����֐���ݒ�
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}
