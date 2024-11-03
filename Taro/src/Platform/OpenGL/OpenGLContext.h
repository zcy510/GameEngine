#pragma once

#include "Taro/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Taro {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_windowHandle;
	};
}