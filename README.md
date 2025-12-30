# 🍒 Cherry
A cross-platform graphical application framework for Visual Effects and Games
# Features
Modern Support for Graphics APIs like Vulkan, DirectX12, Metal

Support for various windowing systems such as GLFW3, Native, SDL

Support for USD and MaterialX
# Example (Current)
```c++
#include "Cherry/Base/App.h"
#include "Cherry/Base/Window.h"
#include "Cherry/Rendering/DX11/DX11Renderer.h"
#include "imgui.h"
int main() {
	Cherry::Base::App app("Hello"); // Creates the app
	Cherry::Rendering::DX11Renderer renderer; // Creates a renderer
	renderer.g_registerDPIScale(); // Registers the dpi scale for ImGui
	Cherry::Base::Window window(Cherry::Base::Window::NATIVE_WINDOWS, "Hello", 10, 10); // Creates a window
	renderer.g_createDevice(window.hwnd); // Creates a device
	renderer.g_initImGui(window.hwnd); // Initialization of ImGui
	while (app.g_isAppRunning) { // Loops while the app is running
		window.g_peekMessages(); // Peeks through event messages
		if (!app.g_isAppRunning) { // Stop the loop if its not rendering
			break;
		}
		
		renderer.g_newFrame(); // Creates a ImGui Frame
		bool open = true;
		ImGui::ShowDemoWindow(&open); 
		renderer.g_resize(); // On Resize
		renderer.g_render(); // Renders the result
		
	}
	renderer.g_cleanupDeviceD3D(); // Cleans up the device
}
```
# Docs
[Source File Link](docs/html/index.html)

[Github Link]()
