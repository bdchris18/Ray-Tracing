#include "App.h"
#include <sstream>
#include <iomanip>

App::App(): wnd(800, 600, "Ray Tracer"){}

int App::Go(){
    while(true){
        if(const auto ecode = Window::ProcessMessages()){
            return *ecode;
        }
        DoFrame();
    }
}

void App::DoFrame(){
    const float t = timer.Peek();
    std::ostringstream oss;
    oss << "Time Elapsed: " << std::setprecision(1) << std::fixed << t << "s";
    wnd.SetTitle(oss.str());
}