#include "Game.hpp"
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
#include "GLincludes.h"
#include "Rectangle.hpp"
#include "TimeSystem.h"

using namespace Utils;

constexpr std::array<Point, 4u> Surround = {Point(0, 1), Point(-1, 0), Point(0, -1), Point(1, 0)};

Game::Game(Myapp* app)
    : ang(PI)
    , chipsize(15)
    , mt(rd())
    , SceneBase(app)
    , wallhack(false)
//    , wallbmp("wall.bmp")
{
    mapsize = {static_cast<int>(getCommon()->mapsize), static_cast<int>(getCommon()->mapsize)};

    playerpos = Vec2(chipsize * 3, chipsize * 3);

    Clustering();

    //上空
    {
        constexpr GLfloat lightPosition[4] = {100.0, 100.0, 100.0, 0};  //光源の位置
        constexpr GLfloat lightDiffuse[3] = {1.0, 1.0, 1.0};            //拡散光
        constexpr GLfloat lightAmbient[3] = {0.0, 0.0, 0.0};            //環境光
        constexpr GLfloat lightSpecular[3] = {0.0, 0.0, 0.0};           //鏡面光

        glLightfv(GL_LIGHT1, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT1, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT1, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT1, GL_SPECULAR, lightSpecular);
        glLightf(GL_LIGHT1, GL_SHININESS, 128);
        glEnable(GL_LIGHT1);
    }

    //手元
    {
        constexpr GLfloat lightPosition[4] = {0.0, 2, -10.0, 1.0};  //光源の位置
        constexpr GLfloat lightDiffuse[3] = {0.6, 0.6, 0.6};        //拡散光
        constexpr GLfloat lightAmbient[3] = {0.4, 0.4, 0.4};        //環境光
        constexpr GLfloat lightSpecular[3] = {0.9, 0.9, 0.9};       //鏡面光

        glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
        glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
        glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
        glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
        glEnable(GL_LIGHT0);
    }

    glEnable(GL_COLOR_MATERIAL);

    debug_eyelevel = 0;

    watch.Start();
}

Game::~Game()
{
    //光源解除
    glDisable(GL_LIGHT0);
    glDisable(GL_LIGHT1);
}

void Game::update()
{
    
#ifdef DEBUG
//    std::cout << TimeSystem::DeltaTime() << std::endl;
#endif  // DEBUG
    double spd = TimeSystem::DeltaTime() * 28;
    double turnspd = 5;

    const auto beforepos = playerpos;

#ifdef DEBUG
    if (Input::IsPressed('z'))
    {
        debug_eyelevel += spd * 2;
    }
    if (Input::IsPressed('x'))
    {
        debug_eyelevel = 0;
    }
#endif  // DEBUG

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

    if (Input::IsClicked('h') && !wallhack)
    {
        wallhack = true;
        hacktime.Start();
    }

    //カメラの角度s
    lookpos = playerpos;
    lookpos.x -= sin(ang);
    lookpos.y -= cos(ang);

    //位置判定
    auto x = (playerpos.x + chipsize / 2) / chipsize;
    auto y = (playerpos.y + chipsize / 2) / chipsize;

    double time;
    switch (mapdata[y][x])
    {
        case MapInfo::Wall:  //壁
#ifdef DEBUG
            if (Input::IsPressed('h'))
            {
                break;
            }
#endif  // DEBUG

            //壁なら戻る
            playerpos = beforepos;
            break;

        case MapInfo::Floor:
            mapdata[y][x] = MapInfo::Walked;
            break;

        case MapInfo::Goal:  //ゴール
            time = watch.getTime() / 1000.0;
            getCommon()->time = time;
            watch.Stop();

            //ハイスコアの更新
            switch (getCommon()->difficulty)
            {
                case Common::Difficulty::small:
                    getCommon()->sbest = std::min(getCommon()->sbest, time);
                    break;
                case Common::Difficulty::medium:
                    getCommon()->mbest = std::min(getCommon()->mbest, time);
                    break;
                case Common::Difficulty::large:
                    getCommon()->lbest = std::min(getCommon()->lbest, time);
                    break;
            }

            changeScene("result");
            break;
    }
}

void Game::draw() const
{
    float diffuse[] = {0.8, 0.8, 0.8, 1.0};
    float specular[] = {0.5, 0.5, 0.5, 1.0};
    float ambient[] = {0.0, 0.0, 0.0, 1.0};

    glPushMatrix();

    float eyelevel = 3.5;

    gluLookAt(playerpos.x, eyelevel + debug_eyelevel, playerpos.y, lookpos.x, eyelevel + (debug_eyelevel * 0.995),
              lookpos.y, 0, 1, 0);

    //光源移動
    static float lpos[4] = {0, 0, 0, 1.0};
    lpos[0] = playerpos.x;
    lpos[1] = eyelevel;
    lpos[2] = playerpos.y;
    glLightfv(GL_LIGHT0, GL_POSITION, lpos);

    glEnable(GL_DEPTH_TEST);
    // glEnable(GL_TEXTURE_2D);

    //光源設定
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 128.0);
    glEnable(GL_LIGHTING);

    //ベースになるものを作る
    Rectangle r(0, 0, 0, chipsize, chipsize, 0, 0, 0);
    r.color = Color(0, 0.7, 0, 0.5);
    r.SetShader(1, 0);

    std::uniform_int_distribution<> randgen(0, 999);

    for (unsigned i = 1; i < mapdata.size() - 1; ++i)
    {
        for (unsigned k = 1; k < mapdata[0].size() - 1; ++k)
        {
            //移動したもの
            auto rr = r.Movedby(r.w * (i), 0, r.h * (k));

            switch (mapdata[k][i])
            {
                case MapInfo::Floor:
                    rr.draw();
                    break;
                case MapInfo::Goal:
                    rr.color = Color(0.8, 0.8, 0);
                    rr.draw();
                    break;
                case MapInfo::Walked:
                    rr.color = Color(0.0, 0.4, 0.7);
                    rr.draw();
                    break;
                case MapInfo::Wall:
#ifdef DEBUG
                    rr.color = Color(0.8, 0.2, 0.2);
                    rr.draw();
#endif  // DEBUG

                    //壁抜きモードなら描画しない
                    if (wallhack && hacktime.getTime() < 10 * 1000)
                    {
                        rr.color = Color(0.7, 0, 0);
                        rr.draw();
                        continue;
                    }
                    //壁

                    //高さ合わせ
                    rr.Moveby(0, r.h / 2, 0);
                    //色
                    rr.color = Color(0.5, 0.2, 0, 0);
                    //シェーダー調整
                    rr.SetShader(1, 0.2);

                    if (mapdata[k + 1][i] != 0)
                    {
                        auto rw = rr.Movedby(0, 0, rr.h / 2);
                        rw.Rotate(90, 0, 0);
                        rw.draw();
                        rw.Moveby(0, 0, -rr.h / 10);
                        rw.draw();
                    }

                    if (mapdata[k - 1][i] != 0)
                    {
                        auto rw = rr.Movedby(0, 0, -rr.h / 2);
                        rw.Rotate(-90, 0, 0);
                        rw.draw();
                        rw.Moveby(0, 0, rr.h / 10);
                        rw.draw();
                    }

                    if (mapdata[k][i + 1] != 0)
                    {
                        auto rw = rr.Movedby(rr.h / 2, 0, 0);
                        rw.Rotate(0, 0, -90);
                        rw.draw();
                        rw.Moveby(-rr.h / 10, 0, 0);
                        rw.draw();
                    }

                    if (mapdata[k][i - 1] != 0)
                    {
                        auto rw = rr.Movedby(-rr.h / 2, 0, 0);
                        rw.Rotate(0, 0, 90);
                        rw.draw();

                        rw.Moveby(rr.h / 10, 0, 0);
                        rw.draw();
                    }

                    break;
            }
        }
    }

    // glDisable(GL_TEXTURE_2D);
    glPopMatrix();

    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
}

void Game::Clustering()
{
    //配列確保
    mapdata.resize(mapsize.y + 4);
    for (auto& v : mapdata)
    {
        v.resize(mapsize.x + 4);
    }

    std::uniform_int_distribution<> randgen(0, 999);

    int number = 2;
    Utils::Point rb;  // right bottom
    std::vector<Point> breakwall;

    const int magicnumber = 3;
    for (int i = 0 + magicnumber; i < mapsize.x + magicnumber; ++i)
    {
        for (int k = 0 + magicnumber; k < mapsize.y + magicnumber; ++k)
        {
            mapdata[i][k] = MapInfo::Wall;
            if ((1 <= i && i < mapsize.x - 1) && (1 <= k && k < mapsize.y - 1))
            {
                if ((i % 2) && (k % 2))
                {
                    mapdata[i][k] = number++;
                    rb = {i, k};
                }
                else if ((i % 2) ^ (k % 2) && (i < mapsize.x - 2) && (k < mapsize.y - 2))
                {
                    if (i % 2)
                    {
                        mapdata[i][k] = -1;
                        rb = {i, k};
                    }
                    else
                    {
                        mapdata[i][k] = -2;
                    }
                    breakwall.emplace_back(Point(i, k));
                }
            }
        }
    }

    std::shuffle(breakwall.begin(), breakwall.end(), mt);

    for (const auto& pos : breakwall)
    {
        int info1, info2;

        if (mapdata[pos.y][pos.x] == -1)
        {
            info1 = mapdata[pos.y + 0][pos.x + 1];
            info2 = mapdata[pos.y + 0][pos.x - 1];
        }
        else if (mapdata[pos.y][pos.x] == -2)  //よこ
        {
            info1 = mapdata[pos.y + 1][pos.x];
            info2 = mapdata[pos.y - 1][pos.x];
        }

        if (info1 != info2 || randgen(mt) < 30)
        {
            std::queue<Point> qu;
            mapdata[pos.y][pos.x] = info1;
            qu.push(pos);

            while (qu.size())
            {
                const auto basepos = qu.front();

                for (const auto& surrond : Surround)
                {
                    const auto pos = basepos.movedBy(surrond);

                    auto& hoge = mapdata[pos.y][pos.x];

                    if (hoge != info1 && hoge != MapInfo::Wall && 0 < hoge)
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
            mapdata[pos.y][pos.x] = MapInfo::Wall;
        }
    }

    // 0と1に2値化
    for (int i = 0; i < mapsize.x; ++i)
    {
        for (int k = 0; k < mapsize.y; ++k)
        {
            mapdata[i][k] = mapdata[i][k] == MapInfo::Wall ? MapInfo::Wall : MapInfo::Floor;
        }
    }
    //ゴール設置
    mapdata[rb.x][rb.y] = MapInfo::Goal;
}
