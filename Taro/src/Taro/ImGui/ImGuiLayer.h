#pragma once

#include "Taro/Core/Layer.h"
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
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }
		void SetDarkThemeColors();
	private:
		float m_Time = 0.0f;
		bool m_BlockEvents = true;
	};
}
