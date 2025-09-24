#include "Cherry/Base/App.h"
#include "Cherry/Base/Window.h"
#include "Cherry/Base/Events.h"
int main(){
	App app = App("Hello");
	Cherry::Base::Window window;
	window.create_window(Cherry::Base::Window::NATIVE_WINDOWS,"Hello",10,10);
	if (Events::WindowEvents::CHERRY_WINDOW_RESIZE) {
		std::cout << "Hello";
	}
}