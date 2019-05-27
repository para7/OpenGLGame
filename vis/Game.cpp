#include "Game.hpp"
#include <iostream>
#include "GLincludes.h"
#include "Rectangle.hpp"

using namespace Utils;

Game::Game()
{
    std::cout << "First Scene" << std::endl;

    //マップの初期化
    for (auto& x : mapdata)
    {
        for (auto& y : x)
        {
            y = 0;
        }
    }

    static GLfloat lightPosition[4] = { 0.0, 100.0, 0.0, 1.0 }; //光源の位置
    static GLfloat lightDiffuse[3] = { 0.3, 0.3, 0.3 }; //拡散光
    static GLfloat lightAmbient[3] = { 0.3, 0.3, 0.3 }; //環境光
    static GLfloat lightSpecular[3] = { 0.2,   0.2, 0.2 }; //鏡面光

    //光源設定
    glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
    glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
    glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
    glEnable(GL_LIGHT1);
}

Game::~Game()
{
    //光源解除
    glDisable(GL_LIGHT1);
}

//
//void drawNormal(float *v0, float *v1)
//{
//    float x0, y0, z0;
//
//    glColor3f(1.0, 0.0, 0.0);
//    glLineWidth(2.0);
//    x0 = v0[0], y0 = v0[1], z0 = v0[2];
//    glPushMatrix();
//    glTranslatef(x0, y0, z0);
//    glBegin(GL_LINES);
//    glVertex3f(0.0, 0.0, 0.0);
//    glVertex3fv(v1);
//    glEnd();
//    glPopMatrix();
//}
void Game::update()
{

}

void Game::draw() const
{
    for (int i = 0; i < mapdata.size(); ++i)
    {
        for (int k = 0; k < mapdata[0].size(); ++k)
        {

        }
    }

//    float diffuse[] = { 0.9, 0.0, 0.9, 1.0 };
//    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float ambient[] = { 0.7, 0.7, 0.7, 1.0 };

    glPushMatrix();
    //glTranslatef(0.0, -0.3, -10);
    //glRotatef(-twist, 0.0, 0.0, 1.0);
    //glRotatef(50, 1.0, 0.0, 0.0);
    //glRotatef(-azimuth, 0.0, 1.0, 0.0);
    //polarview();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);
    glEnable(GL_COLOR_MATERIAL);

    //光源設定
//    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
//    glMaterialf(GL_FRONT, GL_SHININESS, 128.0);
    glEnable(GL_LIGHTING);

    Rectangle r(0, -3, -10, 5, 5, 0, 0, 0);
    r.color = Color(0, 0, 0.8, 0.5);
    //r.Movedby(0, 0, 2).Rotated(90, 0, 0).draw();
    r.draw();                 //中央
    r.color = Color(0.8, 0, 0, 0.5);

    for (int i = -2; i <= 2; ++i)
    {
        for (int k = -2; k <= 2; ++k)
        {
            r.color = ((i+k+10) %2 ==1) ? Color(0.8, 0, 0, 0.5) : Color(0, 0, 0.8, 0.5);
            r.Movedby(r.w * 2 * i, 0, r.h * 2 * k).draw();
        }
    }
    //r.Movedby(2, 0, 0).draw();//右の
    //r.Movedby(0, 0, 2).draw();//右の


    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}