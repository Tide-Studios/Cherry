#pragma once
#include "App.h"
#include <iostream>
#include "gtest/gtest.h"
#include "../Rendering/DX11/DX11Renderer.h"
#ifdef CHERRY_INTERNAL_APP_WIN32
#endif
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
			enum CallBacks {
				CHERRY_WINDOW_RESIZE,
				CHERRY_WINDOW_EXIT,

			};
			static HWND hwnd;
			void create_window(Window::WindowTypes windowType, std::string windowName, int windowX, int windowY);
			static void peek_messages();
			Window();
			~Window();
			static bool isWindowClosed;

			void resize();
			void cleanup();
			void render();
			void new_frame();


		private:
			static void p_createWindowWin32(LPCWSTR windowName, int windowX, int windowY); // Internal Use Only
			
			

	
		};
	}
	
}