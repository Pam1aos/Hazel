#pragma once

#include "Hazel/Application.h"
#include <stdio.h>

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	Hazel::Log::Init();
	Hazel::Log::GetCoreLogger()->info("Initialized Log!");
	Hazel::Log::GetClientLogger()->info("Initialized Log!");	

	printf("Hazel Engine\n");
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}

#endif
