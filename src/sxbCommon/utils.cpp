
#include <string>

#include <bx/macros.h>
//#include <bx/allocator.h>
//#include <bx/compat/ios/malloc.h>
#include <bx/uint32_t.h>

#include <bimg/decode.h>

#include "sxbCommon/utils.h"

SXB_NAMESPACE_BEGIN

static bx::FileReaderI* s_fileReader = NULL;
static bx::FileWriterI* s_fileWriter = NULL;

extern bx::AllocatorI* getDefaultAllocator();
bx::AllocatorI* g_allocator = getDefaultAllocator();

typedef bx::StringT<&g_allocator> String;
static String s_currentDir;

class FileReader : public bx::FileReader
{
	typedef bx::FileReader super;

public:
	virtual bool open(const bx::FilePath& _filePath, bx::Error* _err) override
	{
        
        s_currentDir.set(Utils::getRuntimeDirectory().c_str());
		String filePath(s_currentDir);
		filePath.append(_filePath);
		return super::open(filePath.getPtr(), _err);
	}
};

class FileWriter : public bx::FileWriter
{
	typedef bx::FileWriter super;

public:
	virtual bool open(const bx::FilePath& _filePath, bool _append, bx::Error* _err) override
	{
        s_currentDir.set(Utils::getRuntimeDirectory().c_str());
		String filePath(s_currentDir);
		filePath.append(_filePath);
		return super::open(filePath.getPtr(), _append, _err);
	}
};

bx::AllocatorI* getDefaultAllocator()
{
	BX_PRAGMA_DIAGNOSTIC_PUSH();
	BX_PRAGMA_DIAGNOSTIC_IGNORED_MSVC(4459); // warning C4459: declaration of 's_allocator' hides global declaration
	BX_PRAGMA_DIAGNOSTIC_IGNORED_CLANG_GCC("-Wshadow");
	static bx::DefaultAllocator s_allocator;
	return &s_allocator;
	BX_PRAGMA_DIAGNOSTIC_POP();
}

bx::FileReaderI* getFileReader()
{
	if (s_fileReader == NULL)
	{
		s_fileReader = BX_NEW(g_allocator, FileReader);
	}
	return s_fileReader;
}

bx::FileWriterI* getFileWriter()
{
	if (s_fileWriter == NULL)
	{
		s_fileWriter = BX_NEW(g_allocator, FileWriter);
	}
	return s_fileWriter;
}

bx::AllocatorI*  getAllocator()
{
	return g_allocator;
}

bool Utils::loadShader(const char *FILENAME, bgfx::ShaderHandle & sh_)
{
	bool Result = false;

	std::string shaderPath = getRuntimeDirectory();
    
#if defined(SXB_SYSTEM_IOS)
    shaderPath += "/shaders/";
#else
    switch (::bgfx::getRendererType()) {
        case ::bgfx::RendererType::Noop:
        case ::bgfx::RendererType::Direct3D9:  shaderPath += "/shaders/dx9/";   break;
        case ::bgfx::RendererType::Direct3D11:
        case ::bgfx::RendererType::Direct3D12: shaderPath += "/shaders/dx11/";  break;
        case ::bgfx::RendererType::Gnm:        shaderPath += "/shaders/pssl/";  break;
        case ::bgfx::RendererType::Metal:      shaderPath += "/shaders/metal/"; break;
        case ::bgfx::RendererType::OpenGL:     shaderPath += "/shaders/glsl/";  break;
        case ::bgfx::RendererType::OpenGLES:   shaderPath += "/shaders/essl/";  break;
        case ::bgfx::RendererType::Vulkan:     shaderPath += "/shaders/spirv/"; break;
    }
#endif

	const ::bgfx::Memory *mem = loadMem(shaderPath.c_str(), FILENAME);

	if (mem)
	{
		Result = true;
		sh_ = ::bgfx::createShader(mem);
	}

	return Result;
}

bool Utils::loadProgram(const char* vsName_, const char* fsName_, bgfx::ProgramHandle & ph_)
{
	bool Result = false;
	bgfx::ShaderHandle vsh, fsh;

	if (loadShader(vsName_, vsh) && loadShader(fsName_, fsh))
	{
		Result = true;
		ph_ = bgfx::createProgram(vsh, fsh, true);
	}
	
	return Result;
}

void Utils::imageReleaseCb(void* ptr_, void* userData_)
{
	BX_UNUSED(ptr_);
	bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)userData_;
	bimg::imageFree(imageContainer);
}

void Utils::unload(void* ptr_)
{
	BX_FREE(g_allocator, ptr_);
}

bool Utils::loadTexture(const char* name_, bgfx::TextureHandle & th_, uint64_t flags_, uint8_t skip_, bgfx::TextureInfo* info_, bimg::Orientation::Enum* orientation_)
{
	bool Result = false;
	BX_UNUSED(skip_);
	 th_ = BGFX_INVALID_HANDLE;

	uint32_t size = 0;
	void * data = nullptr;
	
	if (load(getRuntimeDirectory().c_str(), name_, data, size))
	{
		bimg::ImageContainer* imageContainer = bimg::imageParse(g_allocator, data, size);

		if (NULL != imageContainer)
		{
			Result = true;
			if (NULL != orientation_)
			{
				*orientation_ = imageContainer->m_orientation;
			}

			const bgfx::Memory* mem = bgfx::makeRef(
				imageContainer->m_data
				, imageContainer->m_size
				, imageReleaseCb
				, imageContainer
			);
			unload(data);

			if (imageContainer->m_cubeMap)
			{
				th_ = bgfx::createTextureCube(
					uint16_t(imageContainer->m_width)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, flags_
					, mem
				);
			}
			else if (1 < imageContainer->m_depth)
			{
				th_ = bgfx::createTexture3D(
					uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, 1 < imageContainer->m_numMips
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, flags_
					, mem
				);
			}
			else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), flags_))
			{
				th_ = bgfx::createTexture2D(
					uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, flags_
					, mem
				);
			}

			if (bgfx::isValid(th_))
			{
				bgfx::setName(th_, name_);
			}

			if (NULL != info_)
			{
				bgfx::calcTextureSize(
					*info_
					, uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, imageContainer->m_cubeMap
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
				);
			}
		}
	}

	return Result;
}

bool Utils::load(const char *prefix_, const char* filePath_, void *& data_, uint32_t & size_)
{
	bool Result = false;

	size_ = 0;
	std::string all_path = filePath_;
	all_path = prefix_ + all_path;

	FILE *file = fopen(all_path.c_str(), "rb");
	//char * mesg = strerror(errno);

	if (file)
	{
		Result = true;
		fseek(file, 0, SEEK_END);
		size_ = ftell(file);
		fseek(file, 0, SEEK_SET);

		data_ = malloc(size_ + 1);
		fread(data_, 1, size_, file);
		static_cast<char *>(data_)[size_] = '\0';
		fclose(file);
	}

	return Result;
}

const bgfx::Memory* Utils::loadMem(const char *prefix_, const char* filePath_)
{
	std::string all_path = filePath_;
	all_path = prefix_ + all_path;

	FILE *file = fopen(all_path.c_str(), "rb");
	//char * mesg = strerror(errno);

	if (file)
	{
		fseek(file, 0, SEEK_END);
		long fileSize_ = ftell(file);
		fseek(file, 0, SEEK_SET);

		const ::bgfx::Memory *mem = ::bgfx::alloc(fileSize_ + 1);
		fread(mem->data, 1, fileSize_, file);
		mem->data[mem->size - 1] = '\0';
		fclose(file);
		return mem;
	}

	return NULL;
}

SXB_NAMESPACE_END
