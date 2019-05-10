// g1772011
// 石井雄太
//
// Base : ManyFuncs.c

/* anim1*/

#include <stdlib.h>
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include <stdio.h>

float distance = 20., twist = 0., elevation = 30., azimuth = 20.;

/// <summary>
/// 描画を行う
/// </summary>
void display(void)
{
    void my_axis();
    int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);// Z Buffer の有効範囲の指定

    glPushMatrix();
    gluLookAt(0.34*distance, distance*1.732 / 3, -distance, 0., 0., 0., 0., 1., 0.);
    glPushMatrix();
    glutWireCube(1.0);/*　立方体　*/
    glPopMatrix();
    glPopMatrix();

    glDisable(GL_DEPTH_TEST); // Z Bufferの有効範囲の終わり
    glutSwapBuffers();
}

/// <summary>
/// 実行中に常時呼び出される
/// </summary>
void idle(void)
{
    azimuth += 0.01;

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
    gluPerspective(45.0, aspect, 1.0, 50.0);
    
    glMatrixMode(GL_MODELVIEW);

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

    //char型でキーの情報が送られてくるので
    //switch caseで指定できる
}

/// <summary>
/// 初期化
/// </summary>
/// <param name="progname">
/// glutCreateWindowに使うパラメータ
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
    glLoadIdentity();/*行列スタックをクリア*/
    gluPerspective(30., aspect, 1., 50.);
    glMatrixMode(GL_MODELVIEW);/*幾何変換行列スタックを操作対象する*/
}

int main(int argc, char *argv[])
{
    //一番最初のOpenGLの初期化
    glutInit(&argc, argv);

    //自分の初期化関数
    myInit(argv[0]);

    //描画を行う関数を設定
    glutDisplayFunc(display);

    //キーボードの入力を処理する関数を設定
    glutKeyboardFunc(myKbd);

    //ファンクションキー、矢印キーの入力を処理する関数を設定
    glutSpecialFunc(mySkey);

    //マウスのクリックを処理する関数を設定
    glutMouseFunc(myMouse);

    //マウスのドラッグを処理する関数を設定
    glutMotionFunc(myMotion);

    //ウィンドウのサイズが変更されたときに処理する関数を設定
    glutReshapeFunc(myReshape);

    //動作中繰り返し呼び出される関数を設定
    glutIdleFunc(idle);

    glutMainLoop();

    return 0;
}


