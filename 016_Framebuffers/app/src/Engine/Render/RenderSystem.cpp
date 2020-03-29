#include <Engine/Render/RenderSystem.h>

#include <Engine/Render/COpenGLRender.h>

namespace RenderSystemInternal
{
	IRender* render;
}

namespace RenderSystem
{
	IRender* GetRender()
	{
		return RenderSystemInternal::render;
	}

	void Init()
	{
		RenderSystemInternal::render = new COpenGLRender();
	}
}

