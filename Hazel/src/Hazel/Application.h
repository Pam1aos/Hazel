#pragma once
#include "Core.h"
#include "Window.h"

#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/LayerStack.h"

namespace Hazel
{
	class HAZEL_API Application
	{

	private:
		bool OnWindowClose(WindowCloseEvent& e);
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	public:
		Application() ;
		virtual ~Application();
		void Run() ;
		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	};

	// To be defined in the CLIENT (Sandbox)
	Application* CreateApplication();
}

