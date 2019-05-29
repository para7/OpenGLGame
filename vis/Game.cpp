#include "Game.hpp"
#include <iostream>
#include "GLincludes.h"
#include "Rectangle.hpp"
#include "TimeSystem.h"
#include <vector>
#include <queue>
#include <random>

using namespace Utils;

constexpr std::array<Point, 4u> Surround = { Point(0,1),Point(-1,0),Point(0, -1),Point(1, 0) };

void Game::Clustering()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> randgen(0, 999);

    int number = 1;
    Utils::Point rb;
    std::vector<Point> breakwall;

    int Wall = 0;

    for (int i = 0; i < mapsize.x; ++i)
    {
        for (int k = 0; k < mapsize.y; ++k)
        {
            mapdata[k][i] = Wall;
            if ((1 <= i && i < mapsize.x - 1) && (1 <= k && k < mapsize.y - 1))
            {
                if ((i % 2) && (k % 2))
                {
                    mapdata[k][i] = number++;
                    rb = { i, k };
                }
                else if ((i % 2) ^ (k % 2) && (i < mapsize.x - 2) && (k < mapsize.y - 2))
                {
                    if (i % 2)
                    {
                        mapdata[k][i] = -1;
                    }
                    else
                    {
                        mapdata[k][i] = -2;
                    }
                    breakwall.emplace_back(Point(i, k));
                }
            }
        }
    }
    //    breakwall.shuffle();

    for (const auto& pos : breakwall)
    {
        int info1, info2;

        if (mapdata[pos.x][pos.y] == -1)
        {
            info1 = mapdata[pos.x + 0][pos.y + 1];
            info2 = mapdata[pos.x + 0][pos.y - 1];
        }
        else if (mapdata[pos.x][pos.y] == -2)//よこ
        {
            info1 = mapdata[pos.x + 1][pos.y];
            info2 = mapdata[pos.x - 1][pos.y];
        }

        if (info1 != info2 || randgen(mt) < 15)
        {
            std::queue<Point> qu;
            mapdata[pos.x][pos.y] = info1;
            qu.push(pos);

            while (qu.size())
            {
                const auto basepos = qu.front();

                for (const auto& surrond : Surround)
                {
                    const auto pos = basepos.movedBy(surrond);
                    auto& hoge = mapdata[pos.x][pos.y];
                    if (hoge != info1 &&
                        hoge != Wall &&
                        0 < hoge)
                    {
                        hoge = info1;
                        qu.push(pos);
                    }
                }
                qu.pop();
            }
        }
        else
        {
            mapdata[pos.x][pos.y] = Wall;
        }
    }
}

Game::Game()
    : playerpos(0, 0)
    , ang(0)
    , chipsize(15)
{
    std::cout << "First Scene" << std::endl;

    //マップの初期化
    //for (int i = 0; i < mapdata.size(); ++i)
    //{
    //    for (int k = 0; k < mapdata[0].size(); ++k)
    //    {
    //        if (k % 2 == 1 || i % 2 == 1)
    //        {
    //            mapdata[i][k] = 1;
    //        }
    //        else
    //        {
    //            mapdata[i][k] = 0;
    //        }
    //    }
    //}
    Clustering();

    //上空
    {
        constexpr GLfloat lightPosition[4] = { 100.0, 100.0, 100.0, 0 }; //光源の位置
        constexpr GLfloat lightDiffuse[3] = { 1.0, 1.0, 1.0 }; //拡散光
        constexpr GLfloat lightAmbient[3] = { 0.0, 0.0, 0.0 }; //環境光
        constexpr GLfloat lightSpecular[3] = { 0.0,   0.0, 0.0 }; //鏡面光

        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
        glLightf(GL_LIGHT1, GL_SHININESS, 128);
        glEnable(GL_LIGHT1);
    }

    //手元
    {
        constexpr GLfloat lightPosition[4] = { 0.0, 2, -10.0, 1.0 }; //光源の位置
        constexpr GLfloat lightDiffuse[3] = { 0.6, 0.6, 0.6 }; //拡散光
        constexpr GLfloat lightAmbient[3] = { 0.4, 0.4, 0.4 }; //環境光
        constexpr GLfloat lightSpecular[3] = { 0.9, 0.9, 0.9 }; //鏡面光

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glEnable(GL_LIGHT0);
    }

    glEnable(GL_COLOR_MATERIAL);

    debug_eyelevel = 0;
}

Game::~Game()
{
    glDisable(GL_LIGHT0);
    //光源解除
    glDisable(GL_LIGHT1);
}

void Game::update()
{
    double spd = TimeSystem::DeltaTime() * 20;
    double turnspd = 5;

    if (Input::IsPressed('z'))
    {
        debug_eyelevel += spd * 2;
    }
    if (Input::IsPressed('x'))
    {
        debug_eyelevel = 0;
    }

    if (Input::IsPressed('a'))
    {
        ang += spd * turnspd * PI / 180;
    }
    if (Input::IsPressed('d'))
    {
        ang -= spd * turnspd * PI / 180;
    }
    //前進
    if (Input::IsPressed('w'))
    {
        playerpos.x -= sin(ang) * spd;
        playerpos.y -= cos(ang) * spd;
    }
    //後退
    if (Input::IsPressed('s'))
    {
        playerpos.x += sin(ang) * spd;
        playerpos.y += cos(ang) * spd;
    }

    lookpos = playerpos;
    lookpos.x -= sin(ang);
    lookpos.y -= cos(ang);

    //    gluLookAt(playerpos.x, 5, playerpos.y, lookpos.x, 5, lookpos.y, 0, 1, 0);
}

void Game::draw() const
{
    float diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    float specular[] = { 0.5, 0.5, 0.5, 1.0 };
    float ambient[] = { 0.0, 0.0, 0.0, 1.0 };

    glPushMatrix();

    float eyelevel = 0.8;

    gluLookAt(
        playerpos.x, eyelevel + debug_eyelevel, playerpos.y,
        lookpos.x, eyelevel + (debug_eyelevel*0.995), lookpos.y,
        0, 1, 0
    );

    //光源移動
    static float lpos[4] = { 0,0,0,1.0 };
    lpos[0] = playerpos.x;
    lpos[1] = eyelevel;
    lpos[2] = playerpos.y;
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);

    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_TEXTURE_2D);

    //光源設定
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
    glEnable(GL_LIGHTING);

    Rectangle r(0, -3, -10, chipsize, chipsize, 0, 0, 0);
    r.color = Color(0, 0.7, 0, 0.5);
    r.SetShader(1, 0);

    for (int i = 0; i < mapdata.size(); ++i)
    {
        for (int k = 0; k < mapdata[0].size(); ++k)
        {
            auto rr = r.Movedby(r.w * (i - 5), 0, r.h * (k - 5));

            if (0 < mapdata[i][k])
            {
                //床
                rr.draw();
            }
            else//mapdata[i][k] == 0
            {
                //壁

                //高さ合わせ
                rr.Moveby(0, r.h / 2, 0);
                //色
                rr.color = Color(0.5, 0.2, 0, 0);
                //シェーダー調整
                rr.SetShader(1, 0.2);

                auto rw = rr.Movedby(0, 0, rr.h / 2);
                rw.Rotate(90, 0, 0);
                rw.draw();

                rw.Moveby(0, 0, -rr.h);
                rw.Rotate(180, 0, 0);
                rw.draw();

                rw = rr.Movedby(rr.h / 2, 0, 0);
                rw.Rotate(0, 0, -90);
                rw.draw();

                rw.Moveby(rr.w, 0, 0);
                rw.Rotate(0, 0, 180);
                rw.draw();
            }
        }
    }

    //glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}