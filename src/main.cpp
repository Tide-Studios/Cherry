#include "Cherry/Base/App.h"
#include "Cherry/Base/Window.h"
#include "Cherry/Rendering/DX11/DX11Renderer.h"
#include "imgui.h"
#include <imgui_impl_win32.h>
int main() {
	Cherry::Base::App app("Hello");
	Cherry::Rendering::DX11Renderer renderer;
	renderer.g_registerDPIScale();
	Cherry::Base::Window window(Cherry::Base::Window::NATIVE_WINDOWS, "Hello", 10, 10);
	Cherry::Base::Window windows(Cherry::Base::Window::NATIVE_WINDOWS, "Test", 10, 10);
	renderer.g_createDevice(window.hwnd);
	renderer.g_initImGui(window.hwnd);
	while (app.g_isAppRunning) {
		window.g_peekMessages();
		if (!app.g_isAppRunning) {
			break;
		}
		renderer.g_newFrame();
		bool open = true;
		ImGui::ShowDemoWindow(&open);
		renderer.g_resize();
		renderer.g_render();
		
	}
	renderer.g_cleanupDeviceD3D();
}