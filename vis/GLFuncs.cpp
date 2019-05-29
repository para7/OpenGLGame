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
/// 描画を行う
/// </summary>
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClear(GL_COLOR_BUFFER_BIT);

    
    glEnable(GL_DEPTH_TEST);// Z Buffer の有効範囲の指定
    if (!scenemasters.empty())
    {
        scenemasters.top()->Draw();
    }
    glDisable(GL_DEPTH_TEST); // Z Bufferの有効範囲の終わり

    glutSwapBuffers();
}

/// <summary>
/// 実行中に常時呼び出される
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
///ウィンドウサイズを変更したときに呼び出される
/// </summary>
/// <param name="width">
/// ウィンドウ幅
/// </param>
/// <param name="height">
/// ウィンドウ高さ
/// </param>
void myReshape(int width, int height)
{
    const float aspect = (float)width / (float)height;

    //描画領域の設定
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);

    //行列を初期化
    glLoadIdentity();

    //アスペクト比に合わせて描画範囲を再設定
    gluPerspective(45.0, aspect, 1.0, 450.0);

    glMatrixMode(GL_MODELVIEW);

    Window::SetWindowSize(width, height);

    //再描画を予約
    glutPostRedisplay();
}

/// <summary>
/// マウスドラッグ時に呼び出される
/// </summary>
/// <param name="width">
/// カーソル座標x
/// </param>
/// <param name="height">
/// カーソル座標y
/// </param>
void myMotion(int x, int y)
{
    printf(" Motion\n");
    printf("w,h = %d %d\n", x, y);
    glutPostRedisplay();
}

/// <summary>
/// マウスのボタンクリック時に呼び出される
/// </summary>
/// <param name="button">押したボタン</param>
/// <param name="state">押したら0　離したら1</param>
/// <param name="x">座標</param>
/// <param name="y">座標</param>
void myMouse(int button, int state, int x, int y)
{
    printf(" Mouse\n");
    printf("x,y = %d %d\n", x, y);
    printf("button = %d\n", button);
    printf("state = %d\n", state);
    glutPostRedisplay();
}

/// <summary>
/// 特殊キー(矢印、Function等)の処理
/// </summary>
/// <param name="key">押したキー</param>
/// <param name="x">カーソル座標</param>
/// <param name="y">カーソル座標</param>
void mySkey(int key, int x, int y)
{
    printf(" mySkey\n");
    printf("x,y = %d %d\n", x, y);
    printf("key = %d\n", key);
    glutPostRedisplay();
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="progname">
/// glutCreateWindowに使うパラメータ
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

    //背景色
    glClearColor(0.0, 0.0, 0.22, 1.0);

    //垂直同期の設定(できてなさそう)
    glfwSwapInterval(1);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();/*行列スタックをクリア*/
    gluPerspective(45.0, aspect, 1.0, 450.0);
    glMatrixMode(GL_MODELVIEW);/*幾何変換行列スタックを操作対象する*/

    glShadeModel(GL_SMOOTH);

    //片面表示
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

