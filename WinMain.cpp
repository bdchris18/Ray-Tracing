#ifndef UNICODE
#define UNICODE
#endif 

#include "Includes.h"
#include "Window.h"

// LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam){
//     switch(msg){
//         case WM_CLOSE:
//             PostQuitMessage(18);
//             break;
//         // case WM_KEYDOWN:
//             // if(wParam == 'F'){
//             //     SetWindowText(hWnd, L"Ray Trace test");
//             // }
//             // break;
//         // case WM_CHAR:
//         //     static std::string title;
//         //     title.push_back((char)wParam);
//         //     SetWindowText(hWnd, title.c_str());
//         // case WM_LBUTTONDOWN:
//         //     POINTS pt = MAKEPOINTS(lParam);
//         //     std::ostringstream oss;
//         //     oss << "(" << pt.x << "," << pt.y << ")";
//         //     SetWindowText(hWnd, oss.str().c_str());

//     }
//     return DefWindowProc(hWnd, msg, wParam, lParam);
// }

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
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
    }

    if(gResult == -1){
        return -1;
    }
    return msg.wParam;
    // while (true);
    // return 0;
}