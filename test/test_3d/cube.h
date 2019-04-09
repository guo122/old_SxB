
#ifndef CUBE_H_E237017769516AC036ECE9C523B81E19
#define CUBE_H_E237017769516AC036ECE9C523B81E19


#include <stdint.h>  // int32_t

#include <bgfx/bgfx.h>
#include <bgfx/bgfx_utils.h>

#include <sxbTop/defines.h>
#include <sxbCommon/Mesh.h>

#include <string>

#define MAX_IBH		10
#define MAX_VBH		10

class Cube
{
public:
	Cube() :
		m_ready(false),
		m_dbgText("Hello"),
		m_mouseX(0),
		m_mouseY(0),
		m_deltaX(0),
		m_deltaY(0),
		m_eyeX(-13.0f),
		m_eyeY(0.0f),
		m_eyeZ(0.0f),
		m_atX(2.0f),
		m_atY(4.0f),
		m_atZ(0.0f),
		m_key(-1),
		m_mousePressed(false) 
	{}
	~Cube()
	{
		bgfx::shutdown();
	}

public:
	bool init(void* nwh_);

	void update(const uint64_t & frame_ = 0);

public:
	void setdbgText(const std::string &text_) { m_dbgText = text_; }
	void setMouse(const int &x_, const int &y_) { 
		if (m_mousePressed)
		{
			m_deltaX = x_ - m_mouseX + m_deltaX;
			m_deltaY = y_ - m_mouseY + m_deltaY;
			if (m_key == 27) // Num1
			{
				m_eyeX += x_ - m_mouseX;
			}
			else if (m_key == 28) // Num2
			{
				m_eyeY += x_ - m_mouseX;
			}
			else if (m_key == 29) // Num3
			{
				m_eyeZ += x_ - m_mouseX;
			}
			else if (m_key == 16) // Q
			{
				m_atX += x_ - m_mouseX;
			}
			else if (m_key == 22) // W
			{
				m_atY += x_ - m_mouseX;
			}
			else if (m_key == 4) // E
			{
				m_atZ += x_ - m_mouseX;
			}
		}
		m_mouseX = x_,
		m_mouseY = y_;
	}

	void mousePressed() { m_mousePressed = true; }
	void mouseRelease() { m_mousePressed = false; }

	void setKey(const int &key_)
	{
		if (key_ == 35) // Num9
		{
			m_eyeX = -13.0f;
			m_eyeY = 0.0f;
			m_eyeZ = -0.0f;
			m_atX = 2.0f;
			m_atY = 4.0f;
			m_atZ = 0.0f;
		}
		else if (key_ == 26) // Num0
		{
			m_eyeX = 0.0f;
			m_eyeY = 0.0f;
			m_eyeZ = 0.0f;
			m_atX = 0.0f;
			m_atY = 0.0f;
			m_atZ = 0.0f;
		}
		m_key = key_;
	}

private:
	bool m_ready;

	uint32_t m_width;
	uint32_t m_height;
	uint32_t m_debug;
	uint32_t m_reset;

	sxb::Mesh m_bunnyMesh;
	sxb::Mesh m_columnMesh;
	sxb::Mesh m_floorMesh;
	sxb::Mesh m_coordMesh;

	bgfx::VertexBufferHandle m_vbh[MAX_VBH];
	bgfx::IndexBufferHandle m_ibh[MAX_IBH];

	bgfx::ProgramHandle m_program;
	bgfx::ProgramHandle m_program_cube;
	bgfx::ProgramHandle m_program_TextureLighting;

	bgfx::UniformHandle m_texColor;
	bgfx::TextureHandle m_fieldstoneTex;

	sxb::MeshState floorState;

	std::string m_dbgText;

	int m_mouseX;
	int m_mouseY;

	int m_deltaX;
	int m_deltaY;

	float m_eyeX;
	float m_eyeY;
	float m_eyeZ;

	float m_atX;
	float m_atY;
	float m_atZ;

	bool m_mousePressed;

	int m_key;
};

#endif // CUBE_H_E237017769516AC036ECE9C523B81E19