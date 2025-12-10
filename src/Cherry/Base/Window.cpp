#include "Window.h"
#include "Events.h"
#include "../include/imgui/imgui.h"
#include "../include/imgui/backends/imgui_impl_win32.h"
#include "../include/imgui/backends/imgui_impl_dx11.h"
#include <d3d12.h>
#include <dxgi1_4.h>
#include <tchar.h>

#include "../Rendering/DX11/DX11Renderer.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Cherry {
	namespace Base {
		HWND Cherry::Base::Window::hwnd;
		bool Cherry::Base::Window::isWindowClosed;
		
		/*
		* Internal Callback for windows
		*/
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam); 
		/*
		
		*/
		void Window::p_createWindowWin32(LPCWSTR windowName, int windowX, int windowY)
		{
			HINSTANCE hInstance = GetModuleHandle(NULL);
			LPWSTR pCmdLine = GetCommandLineW();
			WNDCLASSW wndClass = {};
			LPCWSTR name = windowName;
			wndClass.lpfnWndProc = WindowProc;
			wndClass.hInstance = hInstance;
			wndClass.lpszClassName = name;
			RegisterClassW(&wndClass);
			
			hwnd = CreateWindowExW(
				0,
				name,
				windowName,
				WS_OVERLAPPEDWINDOW,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				CW_USEDEFAULT,
				NULL,
				NULL,
				hInstance,
				NULL

			);
			if (hwnd == NULL) {
			}
			

			
			ShowWindow(hwnd, SW_SHOWDEFAULT);
			UpdateWindow(hwnd);

			

				
			}
		void Window::resize() {
			
		}

		void Window::cleanup()
		{
			ImGui_ImplDX11_Shutdown();
			ImGui_ImplWin32_Shutdown();
			ImGui::DestroyContext();

			renderer.CleanupDeviceD3D();
			isWindowClosed = true;
		}

	

		
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
			if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam)) {
				return true;
		}
			switch (msg)
			{
			case WM_SIZE:
				if (wParam == SIZE_MINIMIZED)
					return 0;
				Cherry::Base::Window::renderer.g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
				Cherry::Base::Window::renderer.g_ResizeHeight = (UINT)HIWORD(lParam);

			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_PAINT: // For Resizing
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				FillRect(hdc, &ps.rcPaint,(HBRUSH) (COLOR_WINDOW+1));
				EndPaint(hwnd, &ps);
				Events::SendCallBack(Events::WindowEvents::CHERRY_WINDOW_RESIZE);
				break;
			}

			
			
			return DefWindowProcW(hwnd, msg, wParam, lParam);
		}
		void Window::create_window(Window::WindowTypes windowType, std::string windowName, int windowX, int windowY) {
			if (windowType == Window::NATIVE_WINDOWS) {
				std::wstring windowname = std::wstring(windowName.begin(), windowName.end());
				LPCWSTR newString = windowname.c_str();
				Window::p_createWindowWin32(newString, windowX, windowY);
			}
			if (windowType == Window::NATIVE_CROSS) {
				
			}
		}
		void Window::peek_messages()
		{
			MSG msg = { };
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				if (msg.message == WM_QUIT)
					isWindowClosed = true;
			}
		}
		Window::Window()
		{
		}
		Window::~Window()
		{
		}
		
	}
}