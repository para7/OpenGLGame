#pragma once

#include "SceneManager.hpp"
#include <memory>

using Myapp = Mysystem::SceneMaster <std::string>;

void PushSceneManager(std::shared_ptr<Myapp> manager);

void PopSceneManager();

/// <summary>
/// 描画を行う
/// </summary>
void display(void);

/// <summary>
/// 実行中に常時呼び出される
/// </summary>
void idle(void);

/// <summary>
///ウィンドウサイズを変更したときに呼び出される
/// </summary>
/// <param name="width">
/// ウィンドウ幅
/// </param>
/// <param name="height">
/// ウィンドウ高さ
/// </param>
void myReshape(int width, int height);

/// <summary>
/// マウスドラッグ時に呼び出される
/// </summary>
/// <param name="width">
/// カーソル座標x
/// </param>
/// <param name="height">
/// カーソル座標y
/// </param>
void myMotion(int x, int y);

/// <summary>
/// マウスのボタンクリック時に呼び出される
/// </summary>
/// <param name="button">押したボタン</param>
/// <param name="state">押したら0　離したら1</param>
/// <param name="x">座標</param>
/// <param name="y">座標</param>
void myMouse(int button, int state, int x, int y);

/// <summary>
/// 特殊キー(矢印、Function等)の処理
/// </summary>
/// <param name="key">押したキー</param>
/// <param name="x">カーソル座標</param>
/// <param name="y">カーソル座標</param>
void mySkey(int key, int x, int y);

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
void myKbd(unsigned char key, int x, int y);

/// <summary>
/// 初期化
/// </summary>
/// <param name="progname">
/// glutCreateWindowに使うパラメータ
/// </param>
void glInits(char *progname);