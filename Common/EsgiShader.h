#pragma once

#include <cstdint>

class EsgiShader
{
public:
	EsgiShader() {}
	~EsgiShader() {}

	bool LoadVertexShader(const char* filename);
	bool LoadFragmentShader(const char* filename);
	uint32_t CompileShader(uint32_t type, const char* code);

	bool CreateProgram();
	void DestroyProgram();

	inline uint32_t GetProgram() { return m_ProgramObject; }

private:
	uint32_t m_ProgramObject;
	uint32_t m_VertexShader;
	uint32_t m_FragmentShader;

};
