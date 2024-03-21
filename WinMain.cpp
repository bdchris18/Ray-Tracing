#ifndef UNICODE
#define UNICODE
#endif 

#include "Includes.h"
#include "Window.h"
#include "ExceptionHandler.h"
#include "App.h"
#include <sstream>

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try{
        return App{}.Go();
    }
    catch(const ExceptionHandler& eh){
        MessageBoxA(nullptr, eh.what(), eh.GetType(), MB_OK | MB_ICONEXCLAMATION);
    }
    catch(const std::exception& eh){
        MessageBoxA(nullptr, eh.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    catch( ... ){
        MessageBoxA(nullptr, "No Details Available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
    }
    return -1;
    // while (true);
    // return 0;
}