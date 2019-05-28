#include "Game.hpp"
#include <iostream>
#include "GLincludes.h"
#include "Rectangle.hpp"

using namespace Utils;

Game::Game()
{
    std::cout << "First Scene" << std::endl;

    //マップの初期化
    for (int i = 0; i < mapdata.size(); ++i)
    {
        for (int k = 0; k < mapdata[0].size(); ++k)
        {
            if (k % 2 == 1 || i % 2 == 1)
            {
                mapdata[i][k] = 1;
            }
            else
            {
                mapdata[i][k] = 0;
            }
        }
    }

    {
        constexpr GLfloat lightPosition[4] = { 0.0, 100.0, 0.0, 1.0 }; //光源の位置
        constexpr GLfloat lightDiffuse[3] = { 0.3, 0.3, 0.3 }; //拡散光
        constexpr GLfloat lightAmbient[3] = { 0.3, 0.3, 0.3 }; //環境光
        constexpr GLfloat lightSpecular[3] = { 0.2,   0.2, 0.2 }; //鏡面光

        //光源設定
        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
        glEnable(GL_LIGHT1);
    }

    {
        constexpr GLfloat lightPosition[4] = { 0.0, 2.0, -10.0, 1.0 }; //光源の位置
        constexpr GLfloat lightDiffuse[3] = { 0.3, 0.3, 0.3 }; //拡散光
        constexpr GLfloat lightAmbient[3] = { 0.3, 0.3, 0.3 }; //環境光
        constexpr GLfloat lightSpecular[3] = { 0.2,   0.2, 0.2 }; //鏡面光

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glEnable(GL_LIGHT0);
    }

    glEnable(GL_COLOR_MATERIAL);
}

Game::~Game()
{
    glDisable(GL_LIGHT0);
    //光源解除
    glDisable(GL_LIGHT1);
}

void Game::update()
{

}

void Game::draw() const
{
    float diffuse[] = { 0.2, 0.2, 0.2, 1.0 };
    float specular[] = { 0.3, 0.3, 0.3, 1.0 };
    float ambient[] = { 0.7, 0.7, 0.7, 1.0 };

    glPushMatrix();
    glTranslatef(0.0, -0.0, -10);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
    
    //光源設定
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
    glEnable(GL_LIGHTING);

    Rectangle r(0, -3, -10, 5, 5, 0, 0, 0);
    r.color = Color(0.8, 0, 0, 0.5);

    for (int i = 0; i < mapdata.size(); ++i)
    {
        for (int k = 0; k < mapdata[0].size(); ++k)
        {
            if (0 < mapdata[i][k])
            {
                //床
                r.Movedby(r.w * 2 * (i - 5), 0, r.h * 2 * (k-5)).draw();
            }
            else//mapdata[i][k] == 0
            {
                //壁
            }
        }
    }

    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}