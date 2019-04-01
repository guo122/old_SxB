
#include <bx/uint32_t.h>

struct PosColorVertex
{
	float x;
	float y;
	float z;
	uint32_t abgr;
};

static PosColorVertex cubeVertices[] =
{
	{-1.0f,  1.0f,  1.0f, 0xff000000 },
	{ 1.0f,  1.0f,  1.0f, 0xff0000ff },
	{-1.0f, -1.0f,  1.0f, 0xff00ff00 },
	{ 1.0f, -1.0f,  1.0f, 0xff00ffff },
	{-1.0f,  1.0f, -1.0f, 0xffff0000 },
	{ 1.0f,  1.0f, -1.0f, 0xffff00ff },
	{-1.0f, -1.0f, -1.0f, 0xffffff00 },
	{ 1.0f, -1.0f, -1.0f, 0xffffffff },
};

static const uint16_t cubeTriList[] =
{
	0, 1, 2,
	1, 3, 2,
	4, 6, 5,
	5, 6, 7,
	0, 2, 4,
	4, 2, 6,
	1, 5, 3,
	5, 7, 3,
	0, 4, 1,
	4, 5, 1,
	2, 3, 6,
	6, 3, 7,
};

bgfx::ShaderHandle loadShader(const char *FILENAME)
{
	std::string shaderPath = "???";

	switch (bgfx::getRendererType()) {
	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D9:  shaderPath = "../../../bgfx/examples/runtime/shaders/dx9/";   break;
	case bgfx::RendererType::Direct3D11:
	case bgfx::RendererType::Direct3D12: shaderPath = "../../../bgfx/examples/runtime/shaders/dx11/";  break;
	case bgfx::RendererType::Gnm:        shaderPath = "../../../bgfx/examples/runtime/shaders/pssl/";  break;
	case bgfx::RendererType::Metal:      shaderPath = "../../../bgfx/examples/runtime/shaders/metal/"; break;
	case bgfx::RendererType::OpenGL:     shaderPath = "../../../bgfx/examples/runtime/shaders/glsl/";  break;
	case bgfx::RendererType::OpenGLES:   shaderPath = "../../../bgfx/examples/runtime/shaders/essl/";  break;
	case bgfx::RendererType::Vulkan:     shaderPath = "../../../bgfx/examples/runtime/shaders/spirv/"; break;
	}

	//size_t shaderLen = strlen(shaderPath);
	//size_t fileLen = strlen(FILENAME);
	//char *filePath = (char *)malloc(shaderLen + fileLen);
	//memcpy(filePath, shaderPath, shaderLen);
	//memcpy(&filePath[shaderLen], FILENAME, fileLen);

	shaderPath += FILENAME;

	FILE *file = fopen(shaderPath.c_str(), "rb");
	char * mesg = strerror(errno);
	fseek(file, 0, SEEK_END);
	long fileSize = ftell(file);
	fseek(file, 0, SEEK_SET);

	const bgfx::Memory *mem = bgfx::alloc(fileSize + 1);
	fread(mem->data, 1, fileSize, file);
	mem->data[mem->size - 1] = '\0';
	fclose(file);

	return bgfx::createShader(mem);
}