// g1772011
// 石井雄太
//

#include "GLFuncs.hpp"
#include "GL/glut.h"
#include "GL/gl.h"
#include "GL/glu.h"
#include "Init.hpp"
#include "Inputs.hpp"

int main(int argc, char *argv[])
{
    //一番最初のOpenGLの初期化
    glutInit(&argc, argv);

    //自分の初期化関数
    glInits(argv[0]);
	MyInit();

    //描画を行う関数を設定
    glutDisplayFunc(display);

    //キーボードの入力を処理する関数を設定
    glutKeyboardFunc(Input::InputKbd);

    glutKeyboardUpFunc(Input::ReleaseKbd);

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
