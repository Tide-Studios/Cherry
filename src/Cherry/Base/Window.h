#pragma once
#include <d3d11.h>
#include <dxgi1_4.h>
#include <tchar.h>
#include <string.h>
#include <iostream>
namespace Cherry {
	namespace Base {
		class Window {
		public:
			enum WindowTypes {
				// Native Operating System Windowing API (Example such as Win32,
				NATIVE_WINDOWS,
				NATIVE_LINUX,
				NATIVE_MAC,
				NATIVE_CROSS,
				SDL,
				GLFW
			};
			~Window();
			bool isWindowClosed;
			int id;
			HWND hwnd;
	
			
			void g_peekMessages();
			Window(Window::WindowTypes windowType, std::string windowName, int windowX, int windowY);
			private:
			void i_createWindowWin32(LPCWSTR windowName, int windowX, int windowY);
		};
	}
}