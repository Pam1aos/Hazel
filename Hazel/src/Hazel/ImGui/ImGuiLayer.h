#pragma once

#include "Hazel/Layer.h"

namespace Hazel {

	class ImGuiLayer :public Layer
	{

	private:

	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		void OnDetach();

		void Onupdate();
		void OnEvent(Event& event);
	};
}