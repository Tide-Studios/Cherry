#include "Cherry/Base/App.h"
#include "Cherry/Base/Window.h"
#include "Cherry/Base/Events.h"
#include "imgui/imgui.h"
int main(){
	App app = App("Hello");
	Cherry::Base::Window window;
	window.create_window(Cherry::Base::Window::NATIVE_WINDOWS,"Hello",10,10);
	MSG msg{};
	while (!window.isWindowClosed) {
		
		window.peek_messages();
		if (window.isWindowClosed) {
			break;
		}
		window.resize();
		window.new_frame();
		bool hello = true;
		ImGui::ShowDemoWindow(&hello);
		window.render();

		
	}
	app.window.cleanup();
	
}