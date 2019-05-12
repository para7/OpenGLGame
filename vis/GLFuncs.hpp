#pragma once

#include "SceneManager.hpp"
#include <memory>

using Myapp = Mysystem::SceneMaster <std::string>;

void PushSceneManager(std::shared_ptr<Myapp> manager);

void PopSceneManager();

/// <summary>
/// �`����s��
/// </summary>
void display(void);

/// <summary>
/// ���s���ɏ펞�Ăяo�����
/// </summary>
void idle(void);

/// <summary>
///�E�B���h�E�T�C�Y��ύX�����Ƃ��ɌĂяo�����
/// </summary>
/// <param name="width">
/// �E�B���h�E��
/// </param>
/// <param name="height">
/// �E�B���h�E����
/// </param>
void myReshape(int width, int height);

/// <summary>
/// �}�E�X�h���b�O���ɌĂяo�����
/// </summary>
/// <param name="width">
/// �J�[�\�����Wx
/// </param>
/// <param name="height">
/// �J�[�\�����Wy
/// </param>
void myMotion(int x, int y);

/// <summary>
/// �}�E�X�̃{�^���N���b�N���ɌĂяo�����
/// </summary>
/// <param name="button">�������{�^��</param>
/// <param name="state">��������0�@��������1</param>
/// <param name="x">���W</param>
/// <param name="y">���W</param>
void myMouse(int button, int state, int x, int y);

/// <summary>
/// ����L�[(���AFunction��)�̏���
/// </summary>
/// <param name="key">�������L�[</param>
/// <param name="x">�J�[�\�����W</param>
/// <param name="y">�J�[�\�����W</param>
void mySkey(int key, int x, int y);

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
void myKbd(unsigned char key, int x, int y);

/// <summary>
/// ������
/// </summary>
/// <param name="progname">
/// glutCreateWindow�Ɏg���p�����[�^
/// </param>
void glInits(char *progname);