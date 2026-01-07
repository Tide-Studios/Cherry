#include "Shader.h"
#include <plog/Log.h>

namespace Cherry {
	namespace Rendering {
		Shader::Shader()
		{
			PLOG_VERBOSE << "Shader Class Initliazed";
		}
		Shader::~Shader()
		{
		}
		std::string Shader::compileSlangShader(Slang::ComPtr<IGlobalSession> globalSession,std::string file, TargetDesc targetDesc, std::string entryPointName)
		{
			Slang::ComPtr<ISession> session = {};
			Slang::ComPtr<IBlob> diagnostics = {};
			Slang::ComPtr<IBlob> compiledCode = {};
			Slang::ComPtr<IBlob> generatedCode = {};
			Slang::ComPtr<IBlob> codeDiagnostics = {};
			Slang::ComPtr<IComponentType> linkedProgram = {};
			Slang::ComPtr<IEntryPoint> entryPoint = {};
			Slang::ComPtr<IComponentType> program = {};
			Slang::ComPtr<ISlangBlob> diagnosticBlob = {};
			
			SessionDesc sessionDesc = {};
			sessionDesc.targets = &targetDesc;
			sessionDesc.targetCount = 1;
			std::string result;
			if (SLANG_FAILED(globalSession->createSession(sessionDesc, session.writeRef()))) {
				PLOG_ERROR << "Shader failed to create a session";
				return "";
			}

			IModule* module(session->loadModule(file.c_str(), diagnostics.writeRef()));
			if (!module) {
				PLOG_ERROR << "Cherry failed to find shader " << file.c_str();
				return "";
			}
			if (SLANG_FAILED(module->findEntryPointByName(entryPointName.c_str(), entryPoint.writeRef()))) {
				PLOG_ERROR << "Cherry failed to find a entry point";
				return "";
			}
			IComponentType* components[] = { module, entryPoint };
			session->createCompositeComponentType(components, 2, program.writeRef());

			program->link(linkedProgram.writeRef(), diagnosticBlob.writeRef());


			linkedProgram->getTargetCode(
				0,
				generatedCode.writeRef(),
				codeDiagnostics.writeRef()
			);
			if (generatedCode) {
				result = (const char*)generatedCode->getBufferPointer(); // Cleaner result verus having to override the string using assign method
			}
			else if (diagnostics) {
				PLOG_ERROR << diagnostics->getBufferPointer(); // Assumes Diagnostics is true
			}

			return result;
		}

		const char* Shader::compileSlangShader(Slang::ComPtr<IGlobalSession> globalSession, const char* file, TargetDesc targetDesc, const char* entryPointName)
		{
			Slang::ComPtr<ISession> session = {};
			Slang::ComPtr<IBlob> diagnostics = {};
			Slang::ComPtr<IBlob> compiledCode = {};
			Slang::ComPtr<IBlob> generatedCode = {};
			Slang::ComPtr<IBlob> codeDiagnostics = {};
			Slang::ComPtr<IComponentType> linkedProgram = {};
			Slang::ComPtr<IEntryPoint> entryPoint = {};
			Slang::ComPtr<IComponentType> program = {};
			Slang::ComPtr<ISlangBlob> diagnosticBlob = {};

			SessionDesc sessionDesc = {};
			sessionDesc.targets = &targetDesc;
			sessionDesc.targetCount = 1;

			if (SLANG_FAILED(globalSession->createSession(sessionDesc, session.writeRef()))) {
				PLOG_ERROR << "Shader failed to create a session";
				return "";
			}

			IModule* module(session->loadModule(file, diagnostics.writeRef()));
			if (!module) {
				PLOG_ERROR << "Cherry failed to find shader " << file;
				return "";
			}
			if (SLANG_FAILED(module->findEntryPointByName(entryPointName, entryPoint.writeRef()))) {
				PLOG_ERROR << "Cherry failed to find a entry point";
				return "";
			}
			IComponentType* components[] = { module, entryPoint };
			session->createCompositeComponentType(components, 2, program.writeRef());

			program->link(linkedProgram.writeRef(), diagnosticBlob.writeRef());


			linkedProgram->getTargetCode(
				0,
				generatedCode.writeRef(),
				codeDiagnostics.writeRef()
			);
			if (generatedCode) {
				return (const char*)generatedCode->getBufferPointer(); // Converts the C style string containing the generated code into a C++ std::string
			}
			else if (diagnostics) {
				PLOG_ERROR << diagnostics->getBufferPointer(); // Assumes Diagnostics is true
				return "";
			}
			return "";
		}
	}
}