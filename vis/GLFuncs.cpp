#pragma once

#include "GLFuncs.hpp"

#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <stdio.h>
#include <stack>
#include "SceneManager.hpp"
#include <string>
#include <memory>

float distance = 20., twist = 0., elevation = 30., azimuth = 20.;

using Myapp = Mysystem::SceneMaster <std::string>;

std::stack<std::shared_ptr<Myapp>> scenemasters;

/// <summary>
/// �`����s��
/// </summary>
void display(void)
{
    void my_axis();
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glEnable(GL_DEPTH_TEST);// Z Buffer �̗L���͈͂̎w��

    //glPushMatrix();
    //gluLookAt(0.34*distance, distance*1.732 / 3, -distance, 0., 0., 0., 0., 1., 0.);
    //glPushMatrix();
    //glutWireCube(1.0);/*�@�����́@*/
    //glPopMatrix();
    //glPopMatrix();

    //glDisable(GL_DEPTH_TEST); // Z Buffer�̗L���͈͂̏I���

    glutSwapBuffers();

    if (!scenemasters.empty())
    {
        scenemasters.top()->Draw();
    }
}

/// <summary>
/// ���s���ɏ펞�Ăяo�����
/// </summary>
void idle(void)
{
    azimuth += 0.01;

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
    gluPerspective(45.0, aspect, 1.0, 50.0);

    glMatrixMode(GL_MODELVIEW);

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
void myKbd(unsigned char key, int x, int y)
{
    //Sample from c5-2.c

    //switch (key) {
    //case 'w':
    //    wireFlag = !wireFlag;
    //    break;
    //case 'R':
    //    resetview();
    //    break;
    //case KEY_ESC:
    //    exit(0);
    //}

    //char�^�ŃL�[�̏�񂪑����Ă���̂�
    //switch case�Ŏw��ł���
}

/// <summary>
/// ������
/// </summary>
/// <param name="progname">
/// glutCreateWindow�Ɏg���p�����[�^
/// </param>
void myInit(char *progname)
{
    int width = 500, height = 500;
    float aspect = (float)width / (float)height;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize(width, height);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutCreateWindow(progname);
    glClearColor(0.3, 0.3, 0.3, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();/*�s��X�^�b�N���N���A*/
    gluPerspective(30., aspect, 1., 50.);
    glMatrixMode(GL_MODELVIEW);/*�􉽕ϊ��s��X�^�b�N�𑀍�Ώۂ���*/
}