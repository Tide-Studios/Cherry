#include "App.h"
namespace Cherry {
	namespace Base {
		
		App::App(std::string appName) {
			plog::init(plog::verbose, &consoleAppender);
			PLOG_VERBOSE << "Cherry App started:"+appName;
		}

		App::~App() {
			g_isAppRunning = false;
			PLOG_VERBOSE << "Cherry App closed";
		}
		
	}
}