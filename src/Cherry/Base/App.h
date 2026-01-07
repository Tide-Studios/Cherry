#pragma once
// Plog
#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
#include <slang.h>
#include <slang-com-ptr.h>
// Standard Library
#include <list>
// Preprocessor definitons
#ifndef CHERRY_CMAKE // To check if you already defined these preprocessors for Different Systems
	#ifdef WIN32
		#define CHERRY_WINDOWS
#elif __APPLE__
		#define CHERRY_MAC
#elif __linux__
#define CHERRY_LINUX
	#endif

#endif
using namespace slang;
namespace Cherry {
	namespace Base {
		class App {

		public:
			App(std::string appName);
			~App();
			static App& RetriveApplication();
			std::string g_appName;
			std::string directory;
			Slang::ComPtr<IGlobalSession> globalSession;
			SlangGlobalSessionDesc globalSessionDescription;
		//	std::list<Cherry::Base::Window> g_appWindows;
			bool g_isAppRunning;

		private:
			plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
			void i_createSlangGlobalSession(); // Creates a Global Session for Slang
			void i_createMaterialX();
		};
	}
}