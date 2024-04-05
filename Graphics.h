#pragma once
#include "Includes.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <iterator>
#include <cmath>
#include <DirectXMath.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

namespace dx = DirectX;

class Graphics{
    public:
        Graphics() {}
        Graphics(HWND hWnd);
        Graphics(const Graphics&) = delete;
        Graphics& operator=(const Graphics&) = delete;
        ~Graphics();
        void EndFrame();
        void ClearBuffer(float red, float green, float blue) noexcept {
            const float color[] = { red, green, blue, 1.0f };
            pContext->ClearRenderTargetView(pTarget.Get(), color);
            pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
        }
        void SetupBuffers();
        void DrawTestCube(float angle, float rotX, float rotY, float posX, float posY, float posZ);
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> pDevice;
        Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> pDSV;
};