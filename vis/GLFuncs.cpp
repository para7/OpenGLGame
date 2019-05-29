#include "GLFuncs.hpp"

#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <stdio.h>
#include <stack>
#include "SceneManager.hpp"
#include <string>
#include "Inputs.hpp"
#include <iostream>
#include <GLFW/glfw3.h>
#include "TimeSystem.h"
#include "WindowInfo.h"

float distance = 20., twist = 0., elevation = 30., azimuth = 20.;

static std::stack<std::shared_ptr<Myapp>> scenemasters;

void PushSceneManager(std::shared_ptr<Myapp> manager)
{
	scenemasters.push(manager);
}

void PopSceneManager()
{
	if (scenemasters.empty())
	{
		return;
	}
	scenemasters.pop();
}

/// <summary>
/// �`����s��
/// </summary>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);

    
    glEnable(GL_DEPTH_TEST);// Z Buffer �̗L���͈͂̎w��
    if (!scenemasters.empty())
    {
        scenemasters.top()->Draw();
    }
    glDisable(GL_DEPTH_TEST); // Z Buffer�̗L���͈͂̏I���

    glutSwapBuffers();
}

/// <summary>
/// ���s���ɏ펞�Ăяo�����
/// </summary>
void idle(void)
{
//    azimuth += 0.01;

    Input::Update();
    TimeSystem::Update();

    if (!scenemasters.empty())
    {
        scenemasters.top()->Update();
    }

    glutPostRedisplay();
}

/// <summary>
///�E�B���h�E�T�C�Y��ύX�����Ƃ��ɌĂяo�����
/// </summary>
/// <param name="width">
/// �E�B���h�E��
/// </param>
/// <param name="height">
/// �E�B���h�E����
/// </param>
void myReshape(int width, int height)
{
    const float aspect = (float)width / (float)height;

    //�`��̈�̐ݒ�
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    //�s���������
    glLoadIdentity();

    //�A�X�y�N�g��ɍ��킹�ĕ`��͈͂��Đݒ�
    gluPerspective(45.0, aspect, 1.0, 450.0);

    glMatrixMode(GL_MODELVIEW);

    Window::SetWindowSize(width, height);

    //�ĕ`���\��
    glutPostRedisplay();
}

/// <summary>
/// �}�E�X�h���b�O���ɌĂяo�����
/// </summary>
/// <param name="width">
/// �J�[�\�����Wx
/// </param>
/// <param name="height">
/// �J�[�\�����Wy
/// </param>
void myMotion(int x, int y)
{
    printf(" Motion\n");
    printf("w,h = %d %d\n", x, y);
    glutPostRedisplay();
}

/// <summary>
/// �}�E�X�̃{�^���N���b�N���ɌĂяo�����
/// </summary>
/// <param name="button">�������{�^��</param>
/// <param name="state">��������0�@��������1</param>
/// <param name="x">���W</param>
/// <param name="y">���W</param>
void myMouse(int button, int state, int x, int y)
{
    printf(" Mouse\n");
    printf("x,y = %d %d\n", x, y);
    printf("button = %d\n", button);
    printf("state = %d\n", state);
    glutPostRedisplay();
}

/// <summary>
/// ����L�[(���AFunction��)�̏���
/// </summary>
/// <param name="key">�������L�[</param>
/// <param name="x">�J�[�\�����W</param>
/// <param name="y">�J�[�\�����W</param>
void mySkey(int key, int x, int y)
{
    printf(" mySkey\n");
    printf("x,y = %d %d\n", x, y);
    printf("key = %d\n", key);
    glutPostRedisplay();
}

/// <summary>
/// ������
/// </summary>
/// <param name="progname">
/// glutCreateWindow�Ɏg���p�����[�^
/// </param>
void glInits(char *progname)
{
    int width = 500, height = 500;
    float aspect = (float)width / (float)height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    Window::SetWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    glutCreateWindow(progname);

    //�w�i�F
    glClearColor(0.0, 0.0, 0.22, 1.0);

    //���������̐ݒ�(�ł��ĂȂ�����)
    glfwSwapInterval(1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();/*�s��X�^�b�N���N���A*/
    gluPerspective(45.0, aspect, 1.0, 450.0);
    glMatrixMode(GL_MODELVIEW);/*�􉽕ϊ��s��X�^�b�N�𑀍�Ώۂ���*/

    glShadeModel(GL_SMOOTH);

    //�Жʕ\��
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

