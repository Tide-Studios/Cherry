#include "DX11Renderer.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
namespace Cherry {
	namespace Rendering {

		UINT Cherry::Rendering::DX11Renderer::g_ResizeWidth;
		UINT Cherry::Rendering::DX11Renderer::g_ResizeHeight;
		DX11Renderer::DX11Renderer()
		{
		}
		DX11Renderer::~DX11Renderer()
		{
		}
		bool DX11Renderer::g_createDevice(HWND hwnd)
		{
			DXGI_SWAP_CHAIN_DESC SwapChainDescription;
			ZeroMemory(&SwapChainDescription, sizeof(SwapChainDescription));
			SwapChainDescription.BufferCount = 2;
			SwapChainDescription.BufferDesc.Width = 0;
			SwapChainDescription.BufferDesc.Height = 0;
			SwapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			SwapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
			SwapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
			SwapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
			SwapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
			SwapChainDescription.OutputWindow = hwnd;
			SwapChainDescription.SampleDesc.Count = 1;
			SwapChainDescription.SampleDesc.Quality = 0;
			SwapChainDescription.Windowed = TRUE;
			SwapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
			UINT createDeviceFlags = 0;
			createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
			D3D_FEATURE_LEVEL featureLevel;
			const D3D_FEATURE_LEVEL featureLevelArray[2] = { D3D_FEATURE_LEVEL_11_0, D3D_FEATURE_LEVEL_10_0, };
			HRESULT res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &SwapChainDescription, g_SwapChain.GetAddressOf(), g_D3D11Device.GetAddressOf(), &featureLevel, g_D3D11DeviceContext.GetAddressOf());
			if (res == DXGI_ERROR_UNSUPPORTED) // Try high-performance WARP software driver if hardware is not available.
				res = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, createDeviceFlags, featureLevelArray, 2, D3D11_SDK_VERSION, &SwapChainDescription, g_SwapChain.GetAddressOf(), g_D3D11Device.GetAddressOf(), &featureLevel, g_D3D11DeviceContext.GetAddressOf());
			if (res != S_OK)
				return false;

			g_createRenderTarget();
			return true;
		}
		void DX11Renderer::g_cleanupDeviceD3D()
		{
			if (g_SwapChain) { g_SwapChain.Reset(); }
			if (g_D3D11DeviceContext) { g_D3D11DeviceContext.Reset(); }
			if (g_D3D11Device) { g_D3D11Device.Reset(); }
			g_cleanupRenderTarget();
		}
		void DX11Renderer::g_createRenderTarget()
		{
			ComPtr<ID3D11Texture2D> pBackBuffer;
			g_SwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer));
			g_D3D11Device->CreateRenderTargetView(pBackBuffer.Get(), nullptr, g_renderTargetView.GetAddressOf());
			pBackBuffer.Reset();
		}
		void DX11Renderer::g_cleanupRenderTarget()
		{
			if (g_renderTargetView) { g_renderTargetView.Reset(); }
		}
		void DX11Renderer::g_resize()
		{
			if (g_SwapChainOccluded && g_SwapChain->Present(0, DXGI_PRESENT_TEST) == DXGI_STATUS_OCCLUDED)
			{
				::Sleep(10);
			}
			g_SwapChainOccluded = false;
			if (g_ResizeWidth != 0 && g_ResizeHeight != 0)
			{
				g_cleanupRenderTarget();
				g_SwapChain->ResizeBuffers(0, g_ResizeWidth, g_ResizeHeight, DXGI_FORMAT_UNKNOWN, 0);
				g_ResizeWidth = g_ResizeHeight = 0;
				g_createRenderTarget();
			}
		}
		void DX11Renderer::g_initImGui(HWND hwnd)
		{
			
			
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();

			ImGui::StyleColorsDark();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGuiStyle& style = ImGui::GetStyle();
			style.ScaleAllSizes(dpiScale);        // Bake a fixed style scale. (until we have a solution for dynamic style scaling, changing this requires resetting Style + calling this again)
			
			ImGui_ImplWin32_Init(hwnd);
			ImGui_ImplDX11_Init(g_D3D11Device.Get(), g_D3D11DeviceContext.Get());
			// Frames
			
			
		}
		void DX11Renderer::g_registerDPIScale()
		{
			ImGui_ImplWin32_EnableDpiAwareness();
			dpiScale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));
		}
		void DX11Renderer::g_newFrame() {
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
		}
		void DX11Renderer::g_render()
		{
			ImGui::Render();
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
			const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
			g_D3D11DeviceContext->OMSetRenderTargets(1, g_renderTargetView.GetAddressOf(), nullptr);
			g_D3D11DeviceContext->ClearRenderTargetView(g_renderTargetView.Get(), clear_color_with_alpha);
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
			HRESULT hr = g_SwapChain->Present(1, 0);
			g_SwapChainOccluded = (hr == DXGI_STATUS_OCCLUDED);
		}
	}
}