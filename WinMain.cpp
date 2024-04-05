#ifndef UNICODE
#define UNICODE
#endif 

#include "Includes.h"
#include "Window.h"
#include "ExceptionHandler.h"
<<<<<<< Updated upstream
#include "App.h"
#include <sstream>

_Use_decl_annotations_ int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try{
        return App{}.Go();
    }
    catch(const ExceptionHandler& eh){
        MessageBoxA(nullptr, eh.what(), eh.GetType(), MB_OK | MB_ICONEXCLAMATION);
    }
=======

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try{
        //instantiating window object 
        Window wnd(800, 300, "Ray Tracer");
        //message pump
        MSG msg;
        BOOL gResult;
        //constantly checking for messages
        while((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0){

            //generates auxiliary messages, also deals with WM_CHAR
            TranslateMessage(&msg);
            //passes message along to window procedure
            DispatchMessage(&msg);

            if(wnd.kbd.KeyIsPressed(VK_SPACE)){
                MessageBoxA(nullptr, "Something Happened!", "Space Key Was Pressed", MB_OK | MB_ICONEXCLAMATION);
            }
        }

        if(gResult == -1){
            throw WND_LAST_EXCEPT();
        }
        else{
            throw 69;
        }
        return msg.wParam;
    }
    catch(const ExceptionHandler& eh){
        MessageBoxA(nullptr, eh.what(), eh.GetType(), MB_OK | MB_ICONEXCLAMATION);
    }
>>>>>>> Stashed changes
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