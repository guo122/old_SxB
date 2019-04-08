
#ifndef CUBE_H_E237017769516AC036ECE9C523B81E19
#define CUBE_H_E237017769516AC036ECE9C523B81E19


#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbTop/defines.h>
#include <sxbCommon/Mesh.h>

#include <string>

class Cube
{
public:
	Cube(): m_ready(false), m_dbgText("Hello"), m_mouseX(0), m_mouseY(0) {}
	~Cube()
	{
		bgfx::shutdown();
	}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

public:
	void setdbgText(const std::string &text_) { m_dbgText = text_; }
	void setMouse(const int &x_, const int &y_) { m_mouseX = x_, m_mouseY = y_; }

private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	sxb::Mesh* m_bunnyMesh;

	bgfx::ProgramHandle m_program;

	std::string m_dbgText;

	int m_mouseX;
	int m_mouseY;
};

#endif // CUBE_H_E237017769516AC036ECE9C523B81E19