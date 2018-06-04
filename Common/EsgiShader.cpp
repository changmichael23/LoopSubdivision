#include "EsgiShader.h"
#include "glew.h"
#define _CRT_SECURE_NO_WARNINGS 1
#include <cstdio>

uint32_t EsgiShader::CompileShader(uint32_t type, const char* code)
{
	uint32_t shaderObject = glCreateShader(type);
	if (shaderObject != 0)
	{
		glShaderSource(shaderObject, 1, &code, nullptr);
		glCompileShader(shaderObject);
	}
	return shaderObject;
}

bool EsgiShader::LoadVertexShader(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	auto len = ftell(file);			// auto permet de détecter automatiquement le type de retour de la fonction à laquelle la variable est affecté
	rewind(file);
	auto buffer = new char[len+1];
	fread(buffer, len, 1, file);
	buffer[len] = '\0';			// = 0 fonctionne aussi
	m_VertexShader = CompileShader(GL_VERTEX_SHADER, buffer);
	delete[] buffer;							// a cause du new on à la responsabilité de vider la mémoire qu'on alloue

	return (m_VertexShader != 0);
}

bool EsgiShader::LoadFragmentShader(const char* filename)
{
	FILE* file = fopen(filename, "rb");
	fseek(file, 0, SEEK_END);
	auto len = ftell(file);
	rewind(file);
	auto buffer = new char[len+1];
	fread(buffer, len, 1, file);
	buffer[len] = '\0';
	m_FragmentShader = CompileShader(GL_FRAGMENT_SHADER, buffer);
	delete[] buffer;

	return (m_FragmentShader != 0);
}

bool EsgiShader::CreateProgram()
{
	m_ProgramObject = glCreateProgram();
	glAttachShader(m_ProgramObject, m_VertexShader);
	glAttachShader(m_ProgramObject, m_FragmentShader);
	glLinkProgram(m_ProgramObject);

	return true;
}

void EsgiShader::DestroyProgram()
{
	glDetachShader(m_ProgramObject, m_VertexShader);
	glDetachShader(m_ProgramObject, m_FragmentShader);
	glDeleteProgram(m_ProgramObject);
	glDeleteShader(m_VertexShader);
	glDeleteShader(m_FragmentShader);

}