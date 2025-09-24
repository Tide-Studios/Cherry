#include "Window.h"
#include "Events.h"
namespace Cherry {
	namespace Base {
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
			HWND hwnd = CreateWindowExW(
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
			MSG msg = { };
			while (GetMessage(&msg, hwnd, 0, 0) > 0)
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

		}
		
		LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
			switch (msg)
			{
			case WM_DESTROY:
				PostQuitMessage(0);
			case WM_PAINT: // For Resizing
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hwnd, &ps);
				FillRect(hdc, &ps.rcPaint,(HBRUSH) (COLOR_WINDOW+1));
				EndPaint(hwnd, &ps);
				Events::WindowEvents::CHERRY_WINDOW_RESIZE;
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
		Window::Window()
		{
		}
		Window::~Window()
		{
		}
	}
}