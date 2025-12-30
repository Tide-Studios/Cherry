#include "Window.h"
#include "App.h"
#include "../Rendering/DX11/DX11Renderer.h"
#include <imgui_impl_win32.h>

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
namespace Cherry {
	namespace Base {
		Window::Window(Window::WindowTypes windowType, std::string windowName, int windowX, int windowY)
		{
				if (windowType == Window::NATIVE_WINDOWS) {
					std::wstring windowname = std::wstring(windowName.begin(), windowName.end());
					LPCWSTR newString = windowname.c_str();
					Window::i_createWindowWin32(newString, windowX, windowY);
				}
				if (windowType == Window::NATIVE_CROSS) {

				}
		}

		LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	
		void Window::i_createWindowWin32(LPCWSTR windowName, int windowX, int windowY)
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
		Window::~Window()
		{
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
			Cherry::Rendering::DX11Renderer::g_ResizeWidth = (UINT)LOWORD(lParam); // Queue resize
			Cherry::Rendering::DX11Renderer::g_ResizeHeight = (UINT)HIWORD(lParam);

			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			}



			return DefWindowProcW(hwnd, msg, wParam, lParam);
		}
		void Window::g_peekMessages()
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
	}

}