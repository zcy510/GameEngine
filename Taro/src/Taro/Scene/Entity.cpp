#include "trpch.h"
#include "Entity.h"

namespace Taro {


	Entity::Entity(entt::entity handle, Scene* scene)
		:m_EntityHandle(handle), m_Scene(scene)
	{

	}

}