#pragma once
#include "Includes.h"
#include "ExceptionHandler.h"
#include "Keyboard.h"
<<<<<<< Updated upstream
#include "Mouse.h"
#include "Graphics.h"
#include <optional>
#include <memory>
=======
>>>>>>> Stashed changes

class Window{
    public:
        class Exception : public ExceptionHandler{
            public:
                Exception(int line, const char* file, HRESULT hr) noexcept;
                const char* what() const noexcept override;
                virtual const char* GetType() const noexcept;
                static std::string TranslateErrorCode(HRESULT hr) noexcept;
                HRESULT GetErrorCode() const noexcept;
                std::string GetErrorString() const noexcept;
            private:
                HRESULT hr;
        };
    private:
        class WindowClass{
            public:
                static const char* GetName() noexcept;
                static HINSTANCE GetInstance() noexcept;
            private:
                WindowClass() noexcept;
                ~WindowClass();
                WindowClass(const WindowClass&) = delete;
                WindowClass& operator=(const WindowClass&) = delete;
                static constexpr const char* wndClassName = "Ray Tracing Engine Window";
                static WindowClass wndClass;
                HINSTANCE hInst;
        };
    public:
        Window(int width, int height, LPCSTR name);
        ~Window();
        Window(const Window&) = delete;
        Window& operator=(const Window&) = delete;
        void SetTitle(const char* title);
        static std::optional<int> ProcessMessages();
        int GetWidth() { return width; };
        int GetHeight() { return height; };
        Graphics& Gfx();
    private:
        static LRESULT CALLBACK HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        static LRESULT CALLBACK HandleMsgThunk(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
        LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
    public:
        Keyboard kbd;
<<<<<<< Updated upstream
        Mouse mouse;
        Graphics gfx;
=======
>>>>>>> Stashed changes
    private:
        int width;
        int height;
        HWND hWnd;
<<<<<<< Updated upstream
        std::unique_ptr<Graphics> pGfx;
=======
>>>>>>> Stashed changes
};

//error exception helper macro
#define WND_EXCEPT(hr) Window::Exception(__LINE__,__FILE__,hr)
#define WND_LAST_EXCEPT() Window::Exception(__LINE__,__FILE__, GetLastError())