#pragma once
#include "Taro/Scene/Scene.h"
#include "Taro/Core/Core.h"

namespace Taro {

	class SceneHierarchyPanel
	{
	public:
		SceneHierarchyPanel() = default;
		SceneHierarchyPanel(const Ref<Scene>& context);

		void SetSelectedEntity(Entity entity);
		void SetContext(const Ref<Scene>& context);
		void OnImGuiRender();

		Entity GetSelectedEntity() const { return m_SelectionContext; }

	private:
		void DrawEntityNode(Entity entity);
		void DrawComponents(Entity entity);
	private:
		Ref<Scene> m_Context;
		Entity m_SelectionContext;
	};
}