#pragma once

//https://w.atwiki.jp/opengl/pages/67.html
#include <stdio.h>
#include "GLincludes.h"

class testBMP
{
 unsigned long sizeX;  //横
 unsigned long sizeY; //縦
 char *Data;  //画像データ格納
 bool Load(char *filename);
 GLuint texture;
 void TexSet();
public:
 testBMP(char *FileName);
};
