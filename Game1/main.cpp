#include <sgg/graphics.h>
#include "Config.h"
#include"GameState.h"
#include"Player.h"
#include <iostream>
using namespace std;

bool isStart = false;

void draw()
{
    if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {
        isStart = true;
    }
    
    if (isStart) {
        GameState::getInstance()->draw();
    }
    else {
        
        graphics::Brush br;
        br.outline_opacity = 0.0f;
        br.fill_color[0] = 0.0f;
        br.fill_color[1] = 0.0f;
        br.fill_color[2] = 0.0f;


        graphics::drawRect(500, 250, 1000, 500, br);
        graphics::setFont("assets\\font.ttf");
        graphics::Brush br2;
        br2.fill_color[0] = 1.0f;
        br2.fill_color[1] = 1.0f;
        br2.fill_color[2] = 1.0f;

       

        drawText(GameState::getInstance()->getCanvasWidth() / 2 -200 , GameState::getInstance()->getCanvasHeight() / 2 +120 , 40 , "Press Space To Start", br2);




        graphics::Brush br3;
        br3.texture ="assets\\p1.png";
        br3.outline_opacity = 0.0f;
        graphics::drawRect(500, 120, 100, 100, br3);


        graphics::Brush br4;

        br4.fill_opacity = 0.5f;

        drawText(GameState::getInstance()->getCanvasWidth() / 2 - 440, GameState::getInstance()->getCanvasHeight() / 2 - 120, 20, "Moves: ", br4);
        drawText(GameState::getInstance()->getCanvasWidth() / 2 - 480, GameState::getInstance()->getCanvasHeight() / 2 - 100, 20, "Press A for Left", br4);
        drawText(GameState::getInstance()->getCanvasWidth() / 2 - 480, GameState::getInstance()->getCanvasHeight() / 2 - 80, 20, "Press D to Right", br4);
        drawText(GameState::getInstance()->getCanvasWidth() / 2 - 480, GameState::getInstance()->getCanvasHeight() / 2 - 60, 20, "Press W for Jump", br4);


        graphics::Brush br5;
        br5.outline_opacity = 0.5;
        br5.fill_opacity = 0.0f;
        graphics::drawRect(GameState::getInstance()->getCanvasWidth() / 2 - 400, GameState::getInstance()->getCanvasHeight() / 2 - 120, 200, 200, br5);


    }
  
}

void update(float dt)
{
    if (isStart) {
        GameState::getInstance()->update(dt);
    }
}



int main(int argc, char** argv)
{
    graphics::createWindow(1200, 600, "Soldier Game");

    

    GameState::getInstance()->init();


    graphics::setDrawFunction(draw);
    graphics::setUpdateFunction(update);

    

    graphics::setCanvasSize(GameState::getInstance()->getCanvasWidth(), GameState::getInstance()->getCanvasHeight());
    graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

    graphics::startMessageLoop();
    return 0;
}

