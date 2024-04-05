#include "Window.h"
#include <sstream>

//Window class
Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass() noexcept: hInst(GetModuleHandle(nullptr)){
    // const auto pClassName = L"RTrace";
    //register a windows class
    WNDCLASSEX wc = {0};
    //window class size
    wc.cbSize = sizeof(wc);
    //window class style
    wc.style = CS_OWNDC;
    //windows procedure used by wc
    wc.lpfnWndProc = HandleMsgSetup;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    //window instance
    wc.hInstance = GetInstance();
    wc.hIcon = nullptr;
    wc.hCursor = nullptr;
    wc.hbrBackground = nullptr;
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = L"Ray Tracing Engine Window";
    wc.hIconSm = nullptr;
    RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass(){
    UnregisterClassA(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName() noexcept{
    return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept{
    return wndClass.hInst;
}

Window::Window(int width, int height, LPCSTR name): gfx(), width(width), height(height){
    RECT wr;
    wr.left = 100;
    wr.right = width + wr.left;
    wr.top = 100;
    wr.bottom = height + wr.top;
    if(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE) == 0){
        throw WND_LAST_EXCEPT();
    }
    //create window and get hWnd
    hWnd = CreateWindowA(WindowClass::GetName(), name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), this);
    //hWnd = CreateWindowA(WindowClass::GetName(), name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), this);
    if(hWnd == nullptr){
        throw WND_LAST_EXCEPT();
    }
    ShowWindow(hWnd, SW_SHOWDEFAULT);
    pGfx = std::make_unique<Graphics>(hWnd);
}

Window::~Window(){
    DestroyWindow(hWnd);
}

void Window::SetTitle(const char* title){
    if(SetWindowTextA(hWnd, title) == 0){
        throw WND_LAST_EXCEPT();
    }
}

std::optional<int> Window::ProcessMessages(){
    MSG msg;
    while(PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)){
        if(msg.message == WM_QUIT){
            return (int)msg.wParam;
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return {};
}

Graphics& Window::Gfx(){
    return *pGfx;
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    if(msg == WM_NCCREATE){
        //extract pointer to window class from creation data
        const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
        Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);

        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgThunk));
        return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept{
    switch(msg){
        case WM_CLOSE:{
            PostQuitMessage(0);
            return 0;
        }
        case WM_KILLFOCUS:{
            kbd.ClearState();
            break;
        }

        case WM_KEYDOWN:{}
        case WM_SYSKEYDOWN:{
            if(!(lParam & 0x40000000) || kbd.AutoRepeatIsEnabled()){
                kbd.OnKeyPressed(static_cast<unsigned char> (wParam));
            }
            break;
        }
        case WM_KEYUP:{}
        case WM_SYSKEYUP:{
            kbd.OnKeyReleased(static_cast<unsigned char> (wParam));
            break;
        }

        case WM_MOUSEMOVE:{
            POINTS pt = MAKEPOINTS(lParam);
            if(pt.x >= 0 && pt.x < width && pt.y >= 0 && pt.y < height){
                mouse.OnMouseMove(pt.x, pt.y);
                if(!mouse.IsInWindow()){
                    SetCapture(hWnd);
                    mouse.OnMouseEnter();
                }
            }
            else{
                if(wParam & (MK_LBUTTON | MK_RBUTTON)){
                    mouse.OnMouseMove(pt.x, pt.y);
                }
                else{
                    ReleaseCapture();
                    mouse.OnMouseLeave();
                }
            }
        }
        case WM_LBUTTONDOWN:{
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftPressed(pt.x, pt.y);
            break;
        }
        case WM_RBUTTONDOWN:{
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightPressed(pt.x, pt.y);
            break;
        }
        case WM_LBUTTONUP:{
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnLeftReleased(pt.x, pt.y);
            break;
        }
        case WM_RBUTTONUP:{
            const POINTS pt = MAKEPOINTS(lParam);
            mouse.OnRightReleased(pt.x, pt.y);
            break;
        }
        case WM_MOUSEHWHEEL:{
            const POINTS pt = MAKEPOINTS(lParam);
            const int delta = GET_WHEEL_DELTA_WPARAM(wParam);
            mouse.OnWheelDelta(pt.x, pt.y, delta);
            break;
        }

        case WM_CHAR:{
            kbd.OnChar(static_cast<unsigned char> (wParam));
            break;
        }
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

//Window Exceptions
Window::Exception::Exception(int line, const char* file, HRESULT hr) noexcept : ExceptionHandler(line, file), hr(hr){}

const char* Window::Exception::what() const noexcept{
    std::ostringstream oss;
    oss << GetType() << std::endl
        << "[Error Code]" << GetErrorCode() << std::endl
        << "[Description]" << GetErrorString() << std::endl
        << GetOriginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* Window::Exception::GetType() const noexcept{
    return "Exception Window Handler";
}

std::string Window::Exception::TranslateErrorCode(HRESULT hr) noexcept{
    char* pMsgBuff = nullptr;
    // points a pointer to a buffer, ALLOCATE_BUFFER needs a pointer to pointer to work
    DWORD nMsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), reinterpret_cast<LPWSTR>(&pMsgBuff), 0, nullptr);
    if(nMsgLen == 0){
        return "Unidentified error code";
    }
    //take error code and copy into std str
    std::string errorString = pMsgBuff;
    LocalFree(pMsgBuff);
    return errorString;
}

HRESULT Window::Exception::GetErrorCode() const noexcept{
    return hr;
}

std::string Window::Exception::GetErrorString() const noexcept{
    return TranslateErrorCode(hr);
}