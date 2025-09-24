#include "App.h"
#include <plog/Log.h>
#include <plog/Formatters/TxtFormatter.h>
#ifdef CHERRY_INTERNAL_APP_WIN32 
	#include <Windows.h>
#endif
App::App(std::string appName) {
	this->g_appName = appName;
}
App::~App()
{
}
App::System App::getSystem()
{
	std::string operatingSystem;

#ifdef CHERRY_INTERNAL_APP_WIN32
	SYSTEM_INFO p_system_info;
	operatingSystem = "Windows";
#endif

	return System(
		operatingSystem
	);
}
