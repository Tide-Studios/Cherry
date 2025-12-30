#pragma once
// Plog
#include <plog/Log.h>
#include <plog/Init.h>
#include <plog/Formatters/TxtFormatter.h>
#include <plog/Appenders/ColorConsoleAppender.h>
// Standard Library
#include <list>
// Cherry Functions

namespace Cherry {
	namespace Base {
		class App {

		public:
			App(std::string appName);
			~App();
			static App& RetriveApplication();
			std::string g_appName;
		//	std::list<Cherry::Base::Window> g_appWindows;
			bool g_isAppRunning;

		private:
			plog::ColorConsoleAppender<plog::TxtFormatter> consoleAppender;
		};
	}
}