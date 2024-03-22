#pragma once
#include "Includes.h"
#include <d3d11.h>

class Graphics{
    public:
        Graphics() {}
        Graphics(HWND hWnd);
        Graphics(const Graphics&) = delete;
        Graphics& operator=(const Graphics&) = delete;
        ~Graphics();
    private:
        ID3D11Device* pDevice = nullptr;
        IDXGISwapChain* pSwap = nullptr;
        ID3D11DeviceContext* pContext = nullptr;
};