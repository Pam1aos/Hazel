#include "Hazel.h"
#include "Hazel/EntryPoint.h"

#include <glad/glad.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() : Layer("Example") {}

	void OnAttach() override
	{
		// Vertex data for our first triangle (x, y, z)
		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};

		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		const char* vertexSrc =
			"#version 330 core\n"
			"layout(location = 0) in vec3 aPos;\n"
			"void main()\n"
			"{\n"
			"    gl_Position = vec4(aPos, 1.0);\n"
			"}\n";

		const char* fragmentSrc =
			"#version 330 core\n"
			"out vec4 color;\n"
			"void main()\n"
			"{\n"
			"    color = vec4(0.8, 0.3, 0.2, 1.0);\n"
			"}\n";

		unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
		glCompileShader(vertexShader);

		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
		glCompileShader(fragmentShader);

		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);
		glLinkProgram(m_ShaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}

	void OnDetach() override
	{
		glDeleteProgram(m_ShaderProgram);
		glDeleteBuffers(1, &m_VertexBuffer);
		glDeleteVertexArrays(1, &m_VertexArray);
	}

	void OnUpdate() override
	{
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("Tab key is pressed(poll)");

		glUseProgram(m_ShaderProgram);
		glBindVertexArray(m_VertexArray);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}

	void OnEvent(Hazel::Event& event) override
	{
		if (event.GetEventType() == Hazel::EventType::KeyPressed) {
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;

			if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
				HZ_TRACE("Tab key is pressed(event)");

			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}

private:
	unsigned int m_VertexArray = 0;
	unsigned int m_VertexBuffer = 0;
	unsigned int m_ShaderProgram = 0;
};



class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox()
	{
	}
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}
