#include "Game.hpp"
#include <iostream>
#include "GLincludes.h"
#include "Rectangle.hpp"


Game::Game()
    : pos(5, 0)
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

    float diffuse[] = { 0.9, 0.0, 0.9, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };
    float ambient[] = { 0.4, 0.4, 0.4, 1.0 };

    glPushMatrix();
    //glTranslatef(0.0, -0.3, -10);
    //    glRotatef(-twist, 0.0, 0.0, 1.0);
    //glRotatef(50, 1.0, 0.0, 0.0);
    //    glRotatef(-azimuth, 0.0, 1.0, 0.0);
        //polarview();
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);

    //光源設定
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
//    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
    glMaterialf(GL_FRONT, GL_SHININESS, 70.0);
    glEnable(GL_LIGHTING);

    Rectangle r(0, 0, -10, 1, 1, 60, 0, 0);
    r.color = Color(0.8, 0, 0.8, 0.5);
    r.draw();                 //中央
    r.Movedby(3, 0, 0).draw();//右の
    r.Moveby(-3, 0, 0);
    
    r.draw();                 //左の
    r.Rotate(0, 45, 0);
    r.Movedby(0, 4, -4).draw();//左の奥の
    r.Rotated(0, 0, 30).Movedby(0, -2, 2).draw();//左の手前の




    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}