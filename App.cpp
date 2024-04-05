#include "App.h"
#include <sstream>
#include <iomanip>
#include <time.h>

App::App() : wnd(800, 600, "Ray Tracer") { posX = 0; posY = 0; posZ = 5.0f; }

int App::Go(){
    while(true){
        if(const auto ecode = Window::ProcessMessages()){
            return *ecode;
        }
        DoFrame();
    }
}

void App::DoFrame(){
    srand((unsigned)time(NULL));
    if (wnd.kbd.KeyIsPressed('D') && posX < wnd.GetWidth() / 4.0f) {
        posX += 0.05f;
    }
    else if (wnd.kbd.KeyIsPressed('A') && posX > -(wnd.GetWidth() / 4.0f)){
        posX -= 0.05f;
    }
    if (wnd.kbd.KeyIsPressed('W') && posZ < 10) {
        posZ += 0.05f;
    }
    else if (wnd.kbd.KeyIsPressed('S') && posZ > 0) {
        posZ -= 0.05f;
    }
    if (wnd.kbd.KeyIsPressed(VK_SPACE) && posY < wnd.GetHeight() / 4.0f) {
        posY += 0.05f;
    }
    else if (wnd.kbd.KeyIsPressed(VK_SHIFT) && posX > -(wnd.GetHeight() / 4.0f)) {
        posY -= 0.05f;
    }
    
    wnd.Gfx().ClearBuffer(0, 0, 0);
    wnd.Gfx().DrawTestCube(timer.Peek(), wnd.mouse.GetPosX() / 400.0f - 1.0f, -wnd.mouse.GetPosY() / 300.0f + 1.0f, posX, posY, posZ);
    wnd.Gfx().DrawTestCube(0, 45.0f, 45.0f, 3.0, 0, 6.0);
    wnd.Gfx().EndFrame();
}