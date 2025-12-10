#pragma once
#ifdef _WIN32 
#include "Windows.h"
#include "wrl/client.h"
#include "d3d11.h"
#include "dxgi.h"
#include <dxgi1_5.h>
#include "imgui/backends/imgui_impl_dx11.h"
#include "imgui/imgui.h"
using namespace Microsoft::WRL;

namespace Cherry {
	namespace Rendering {
		class DX11Renderer {

		public:
			ComPtr<ID3D11Device> g_D3D11Device;
			ComPtr<ID3D11DeviceContext> g_D3D11DeviceContext;
			ComPtr<IDXGISwapChain> g_SwapChain;
			ComPtr<ID3D11RenderTargetView> g_renderTargetView;
			bool g_SwapChainOccluded;
			UINT g_ResizeWidth = 0;
			UINT g_ResizeHeight = 0;
			bool CreateDevice(HWND hwnd);
			void CleanupDeviceD3D();
			void CreateRenderTarget();
			void CleanupRenderTarget();
			void Resize();
			void createImGui();
			void render();
		};
	}
}
#endif