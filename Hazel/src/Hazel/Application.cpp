#include "hzpch.h"
#include "Hazel/Application.h"

#include "Hazel/Log.h"
#include "Hazel/Events/ApplicationEvent.h"

#include<GLFW/glfw3.h>

namespace Hazel
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback([](Event& e) {
		});
	}

	void Application::Run()
	{


		while (m_Running)
		{
			// Main loop code here
			glClearColor(0.1f, 0.1f, 0.1f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Window->OnUpdate();
		}
	}
}
