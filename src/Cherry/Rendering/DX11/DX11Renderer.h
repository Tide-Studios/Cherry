#pragma once
#include "Windows.h"
#include "wrl/client.h"
#include "d3d11.h"
#include "dxgi.h"
#include <dxgi1_5.h>

using namespace Microsoft::WRL;

namespace Cherry {
	namespace Rendering {
		class DX11Renderer {

		public:
			DX11Renderer();
			~DX11Renderer();
			ComPtr<ID3D11Device> g_D3D11Device;
			ComPtr<ID3D11DeviceContext> g_D3D11DeviceContext;
			ComPtr<IDXGISwapChain> g_SwapChain;
			ComPtr<ID3D11RenderTargetView> g_renderTargetView;
			bool g_SwapChainOccluded;
			static UINT g_ResizeWidth;
			static UINT g_ResizeHeight;
			bool g_createDevice(HWND hwnd);
			void g_cleanupDeviceD3D();
			void g_createRenderTarget();
			void g_cleanupRenderTarget();
			void g_resize();
			void g_initImGui(HWND hwnd);
			void g_registerDPIScale();
			void g_newFrame();
			void g_render();
		private:
			float dpiScale;
		};
	}
}