#include "App.h"
#include <MaterialXCore/Document.h>
namespace Cherry {
	namespace Base {
		
		App::App(std::string appName) {
			plog::init(plog::verbose, &consoleAppender);
			PLOG_VERBOSE << "Cherry App initialized" << appName;
			i_createMaterialX();
			i_createSlangGlobalSession();
		}

		App::~App() {
			PLOG_VERBOSE << "Cherry App closed";
			g_isAppRunning = false;
		}


		void App::i_createSlangGlobalSession()
		{
			createGlobalSession(&globalSessionDescription, globalSession.writeRef());
			PLOG_VERBOSE << "Created Slang Global Session";
		}

		void App::i_createMaterialX()
		{
			PLOG_VERBOSE << "MaterialX Verision:" << MaterialX::getVersionString();
		}
		
	}
}