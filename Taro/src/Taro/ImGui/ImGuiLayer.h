#pragma once

#include "Taro/Layer.h"
#include "Taro/Events/ApplicationEvent.h"
#include "Taro//Events/KeyEvent.h"
#include "Taro/Events/MouseEvent.h"

namespace Taro {
	class TARO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender();

		void Begin();
		void End();
	
	private:
		float m_Time = 0.0f;
	};
}
