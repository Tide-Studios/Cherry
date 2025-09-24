#pragma once
#include <iostream>
/*
* \def Test
* \ param NONE
	Preprocessor definitons in one place for better useability
*/
#if defined(_WIN32) || defined(__WIN32__) || defined(__WIN32) || defined(__NT__)
	#ifdef _WIN64
		#define CHERRY_INTERNAL_APP_WIN32
	#else
		#error "32bit systems are not supported by Cherry"
	#endif
#endif
#ifdef __LINUX__
	#define CHERRY_INTERNAL_APP_LINUX
#endif
#ifdef __APPLE__
	#define CHERRY_INTERNAL_APP_APPLE
#endif
class App {
 public:
	 std::string g_appName;
	 bool appRunning;
	 App(std::string appName);
	 ~App();
 private:
	 struct System {
		 std::string p_operatingSystem;
	 };
	 System getSystem();
};