
#include <string>

#include <bx/uint32_t.h>
#include <bgfx/bgfx.h>

#include "sxbCommon/utils.h"

SXB_NAMESPACE_BEGIN

bool Utils::loadShader(const char *FILENAME, bgfx::ShaderHandle & sh_)
{
	bool Result = false;

	std::string shaderPath = "???";

	switch (::bgfx::getRendererType()) {
	case ::bgfx::RendererType::Noop:
	case ::bgfx::RendererType::Direct3D9:  shaderPath = "../../../runtime/shaders/dx9/";   break;
	case ::bgfx::RendererType::Direct3D11:
	case ::bgfx::RendererType::Direct3D12: shaderPath = "../../../runtime/shaders/dx11/";  break;
	case ::bgfx::RendererType::Gnm:        shaderPath = "../../../runtime/shaders/pssl/";  break;
	case ::bgfx::RendererType::Metal:      shaderPath = "../../../runtime/shaders/metal/"; break;
	case ::bgfx::RendererType::OpenGL:     shaderPath = "../../../runtime/shaders/glsl/";  break;
	case ::bgfx::RendererType::OpenGLES:   shaderPath = "../../../runtime/shaders/essl/";  break;
	case ::bgfx::RendererType::Vulkan:     shaderPath = "../../../runtime/shaders/spirv/"; break;
	}

	shaderPath += FILENAME;

	FILE *file = fopen(shaderPath.c_str(), "rb");
	char * mesg = strerror(errno);

	if (file)
	{
		Result = true;
		fseek(file, 0, SEEK_END);
		long fileSize = ftell(file);
		fseek(file, 0, SEEK_SET);

		const ::bgfx::Memory *mem = ::bgfx::alloc(fileSize + 1);
		fread(mem->data, 1, fileSize, file);
		mem->data[mem->size - 1] = '\0';
		fclose(file);
		sh_ = ::bgfx::createShader(mem);
	}

	return Result;
}


SXB_NAMESPACE_END