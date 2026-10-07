#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Hazel
{
	class HAZEL_API Application
	{

	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	public:
		Application() ;
		virtual ~Application() {};
		void Run() ;
	};

	// To be defined in the CLIENT (Sandbox)
	Application* CreateApplication();
}

