#include "hzpch.h"
#include "ImGuiLayer.h"
#include "Hazel/Application.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"
#include "GLFW/glfw3.h"

#include "Hazel/Events/MouseEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/ApplicationEvent.h"
#include "glad/glad.h"

namespace Hazel {

#define IMGUI_MAP_KEY(ImGuiKeyName, GlfwKeyName)  io.KeyMap[ImGuiKeyName] = GlfwKeyName;

	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	//ImGuiLayer::ImGuiLayer()
	//{
	//}


	ImGuiLayer::~ImGuiLayer()
	{
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;


		// ����ӳ��
		IMGUI_MAP_KEY(ImGuiKey_Tab, GLFW_KEY_TAB);
		IMGUI_MAP_KEY(ImGuiKey_LeftArrow, GLFW_KEY_LEFT);
		IMGUI_MAP_KEY(ImGuiKey_RightArrow, GLFW_KEY_RIGHT);
		IMGUI_MAP_KEY(ImGuiKey_UpArrow, GLFW_KEY_UP);
		IMGUI_MAP_KEY(ImGuiKey_DownArrow, GLFW_KEY_DOWN);
		IMGUI_MAP_KEY(ImGuiKey_PageUp, GLFW_KEY_PAGE_UP);
		IMGUI_MAP_KEY(ImGuiKey_PageDown, GLFW_KEY_PAGE_DOWN);
		IMGUI_MAP_KEY(ImGuiKey_Home, GLFW_KEY_HOME);
		IMGUI_MAP_KEY(ImGuiKey_End, GLFW_KEY_END);
		IMGUI_MAP_KEY(ImGuiKey_Insert, GLFW_KEY_INSERT);
		IMGUI_MAP_KEY(ImGuiKey_Delete, GLFW_KEY_DELETE);
		IMGUI_MAP_KEY(ImGuiKey_Backspace, GLFW_KEY_BACKSPACE);
		IMGUI_MAP_KEY(ImGuiKey_Space, GLFW_KEY_SPACE);
		IMGUI_MAP_KEY(ImGuiKey_Enter, GLFW_KEY_ENTER);
		IMGUI_MAP_KEY(ImGuiKey_Escape, GLFW_KEY_ESCAPE);
		IMGUI_MAP_KEY(ImGuiKey_KeyPadEnter, GLFW_KEY_KP_ENTER);
		IMGUI_MAP_KEY(ImGuiKey_A, GLFW_KEY_A);
		IMGUI_MAP_KEY(ImGuiKey_C, GLFW_KEY_C);
		IMGUI_MAP_KEY(ImGuiKey_V, GLFW_KEY_V);
		IMGUI_MAP_KEY(ImGuiKey_X, GLFW_KEY_X);
		IMGUI_MAP_KEY(ImGuiKey_Y, GLFW_KEY_Y);
		IMGUI_MAP_KEY(ImGuiKey_Z, GLFW_KEY_Z);
		ImGui_ImplOpenGL3_Init("#version 410");
	}


	void ImGuiLayer::OnDetach()
	{
	}

	void ImGuiLayer::OnUpdate()
	{


		ImGuiIO& io = ImGui::GetIO();
		Application&app = Application::Get();


		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		
		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();


		static bool show=true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents)
		{
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(std::bind(&ImGuiLayer::OnMouseButtonReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMovedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScrolledEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyReleasedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTypedEvent, this, std::placeholders::_1));
		dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::OnWindowResizeEvent, this, std::placeholders::_1));
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = true;
		io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL] || io.KeysDown[GLFW_KEY_RIGHT_CONTROL];
		io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT] || io.KeysDown[GLFW_KEY_RIGHT_SHIFT];
		io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT] || io.KeysDown[GLFW_KEY_RIGHT_ALT];
		io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER] || io.KeysDown[GLFW_KEY_RIGHT_SUPER];
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.KeysDown[e.GetKeyCode()] = false;
		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000) {
			io.AddInputCharacter((unsigned short)keycode);
		}

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}


}