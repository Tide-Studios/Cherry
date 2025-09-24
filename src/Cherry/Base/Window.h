#pragma once
#include "App.h"
#include <iostream>
#include "gtest/gtest.h"
#ifdef CHERRY_INTERNAL_APP_WIN32
	#include "Windows.h"
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
			void create_window(Window::WindowTypes windowType, std::string windowName, int windowX, int windowY);
			Window();
			~Window();

		private:
			static void p_createWindowWin32(LPCWSTR windowName, int windowX, int windowY); // Internal Use Only
			

	
		};
	}
	
}