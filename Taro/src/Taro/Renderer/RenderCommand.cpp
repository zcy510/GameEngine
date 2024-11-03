#include "trpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace Taro {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();
}