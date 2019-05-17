
#ifndef UTILS_H_D7F61747FB3C5E68C6A972C2521B0AC2
#define UTILS_H_D7F61747FB3C5E68C6A972C2521B0AC2

#include <bx/allocator.h>
#include <bx/readerwriter.h>
#include <bx/file.h>

#include <bgfx/bgfx.h>
#include <bimg/bimg.h>

#include <string>

#include "sxbCommon/defines.h"

SXB_NAMESPACE_BEGIN

bx::FileReaderI* getFileReader();
bx::FileWriterI* getFileWriter();
bx::AllocatorI*  getAllocator();

class Utils
{
public:
    static bool loadShader(const char *FILENAME, ::bgfx::ShaderHandle & sh_);

    static bool loadProgram(const char* vsName_, const char* fsName_, ::bgfx::ProgramHandle & ph_);

	static bool loadTexture(
		const char* name_, 
		::bgfx::TextureHandle & th_,
		uint64_t flags_ = BGFX_TEXTURE_NONE | BGFX_SAMPLER_NONE, 
		uint8_t skip_ = 0, 
		::bgfx::TextureInfo* info_ = NULL, 
		bimg::Orientation::Enum* orientation_ = NULL
	);

	static bool load(const char *prefix_, const char* filePath_, void *& data_, uint32_t & size_);

	static const ::bgfx::Memory* loadMem(const char *prefix_, const char* filePath_);

	static void unload(void* ptr_);
	
	static void imageReleaseCb(void* ptr_, void* userData_);
    
    static void* load(bx::FileReaderI* _reader, bx::AllocatorI* _allocator, const char* _filePath, uint32_t* _size);
    
    static bgfx::TextureHandle loadTexture(const char* _name, uint64_t _flags = BGFX_TEXTURE_NONE|BGFX_SAMPLER_NONE, uint8_t _skip = 0, bgfx::TextureInfo* _info = NULL, bimg::Orientation::Enum* _orientation = NULL);
    
public:
    // different platform
    static const std::string & getRuntimeDirectory();
    
    static bool getMem(double &residentMem_, double &virtualMem_);
    
protected:
    static bgfx::TextureHandle loadTextureImpl(bx::FileReaderI* _reader, const char* _filePath, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation);
    
private:
	Utils() {};
	~Utils() 
	{
		//BX_DELETE(g_allocator, s_fileReader);
		//s_fileReader = NULL;

		//BX_DELETE(g_allocator, s_fileWriter);
		//s_fileWriter = NULL;
	};
    
private:
    // different platform
    static std::string s_runtimeDirectory;
};

SXB_NAMESPACE_END

#endif // UTILS_H_D7F61747FB3C5E68C6A972C2521B0AC2
