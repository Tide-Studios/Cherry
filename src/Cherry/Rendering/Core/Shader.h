#pragma once
#include <slang.h>
#include <slang-com-ptr.h>
#include <string>
#include <iostream>
using namespace slang;
namespace Cherry {
	namespace Rendering {
		class Shader {
		public:
			Shader();
			~Shader();
			TargetDesc targetDesc = {};
			// Method compiling Slang shader files to your choice of output
			std::string compileSlangShader(Slang::ComPtr<IGlobalSession> session,std::string file, TargetDesc targetdesc, std::string entryPointName);
			const char* compileSlangShader(Slang::ComPtr<IGlobalSession> session, const char* file, TargetDesc targetdesc, const char* entryPointName); // Supported for those who need C style strings
			void writeSlangShaderToFile(std::string slangFile, std::string outputFile);
			void writeSlangShaderToFile();
		};
	}
}