#include "Shader.h"
#include "../Utils/Log.h"
#include <fstream>
#include <assert.h>

Shader::Shader() :
	m_programId(0),
	m_vertShaderId(0),
	m_fragShaderId(0)
{
}

Shader::~Shader()
{
}

Shader* Shader::LoadFromFile(const char *vertexShaderFile,
							 const char *fragmentShaderFile)
{
	printf("compiling shaders:\n");
	printf("vertex: %s\n", vertexShaderFile);
	printf("fragment: %s\n", fragmentShaderFile);
	
	Shader *shader = new Shader();
	
	shader->m_vertShaderId = CompileShader(GL_VERTEX_SHADER, vertexShaderFile);
	if (shader->m_vertShaderId == 0)
	{
		assert(false);
		delete shader;
		return NULL;
	}
	
	shader->m_fragShaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderFile);
	if (shader->m_fragShaderId == 0)
	{
		assert(false);
		delete shader;
		return NULL;
	}
	
	shader->m_programId = glCreateProgram();
	
	glAttachShader(shader->m_programId, shader->m_vertShaderId);
	glAttachShader(shader->m_programId, shader->m_fragShaderId);
	
	shader->LinkProgram();
	
	return shader;
}

void Shader::UseProgram()
{
	glUseProgram(m_programId);
}

void Shader::BindVertexChannel(unsigned channel, const char *name)
{
	glBindAttribLocation(m_programId, channel, name);
}

void Shader::SetParameter(const char *name, float val)
{
	int uniformParam = glGetUniformLocation(m_programId, name);
	assert(uniformParam != -1);
	
	glUniform1f(uniformParam, val);
}

void Shader::SetParameter(uint32_t location, float val)
{
	glUniform1f(location, val);
}

void Shader::SetParameter(const char *name, float val1, float val2, float val3)
{
	int uniformParam = glGetUniformLocation(m_programId, name);
	assert(uniformParam != -1);
	
	glUniform3f(uniformParam, val1, val2, val3);
}

void Shader::SetParameter(uint32_t location, float val1, float val2, float val3)
{
	glUniform3f(location, val1, val2, val3);
}

void Shader::SetParameter(const char *name, float val1, float val2, float val3, float val4)
{
	int uniformParam = glGetUniformLocation(m_programId, name);
	if (uniformParam == -1)
		return;
	
	glUniform4f(uniformParam, val1, val2, val3, val4);
}

void Shader::SetParameter(uint32_t location, float val1, float val2, float val3, float val4)
{
	glUniform4f(location, val1, val2, val3, val4);
}

void Shader::SetParameter(const char *name, const sm::Vec3 &val)
{
	SetParameter(name, val.x, val.y, val.z);
}

void Shader::SetParameter(uint32_t location, const sm::Vec3 &val)
{
	SetParameter(location, val.x, val.y, val.z);
}

void Shader::SetParameter(const char *name, const sm::Vec4 &val)
{
	SetParameter(name, val.x, val.y, val.z, val.w);
}

void Shader::SetTextureParameter(const char *name, unsigned channel, unsigned texId)
{
	int uniformParam = glGetUniformLocation(m_programId, name);
	if (uniformParam == -1)
		return;

	glActiveTexture(GL_TEXTURE0 + channel);
	glBindTexture(GL_TEXTURE_2D, texId);
	
	glUniform1i(uniformParam, channel);
	
}

void Shader::SetTextureParameter(uint32_t location, unsigned channel, unsigned texId)
{
	glActiveTexture(GL_TEXTURE0 + channel);
	glBindTexture(GL_TEXTURE_2D, texId);
	
	glUniform1i(location, channel);
}

void Shader::SetMatrixParameter(const char *name, const sm::Matrix &matrix)
{
	int uniformParam = glGetUniformLocation(m_programId, name);
	assert(uniformParam != -1);
	
	glUniformMatrix4fv(uniformParam, 1, false, matrix);
}

void Shader::SetMatrixParameter(uint32_t location, const sm::Matrix &matrix)
{
	glUniformMatrix4fv(location, 1, false, matrix);
}

GLuint Shader::CompileShader(GLenum shaderType, const char* file)
{
	std::ifstream fileStream(file, std::ios::binary);
	if (!fileStream.is_open() || fileStream.fail())
	{
		Log::LogT("Couldn't open shader file: %s", file);
		assert(false);
		return NULL;
	}
	
	fileStream.seekg(0, std::ios::end);
	unsigned fileSize = fileStream.tellg();
	fileStream.seekg(0, std::ios::beg);
	
	char *fileContent = new char[fileSize + 1];
	fileStream.read(fileContent, fileSize);
	fileStream.close();
	fileContent[fileSize] = 0;

	GLchar **cipa = new GLchar*[2];
	cipa[0] = fileContent;
	cipa[1] = 0;
	
	GLuint shaderId = glCreateShader(shaderType);
    //glShaderSource(shaderId, 1, (const GLchar**)&fileContent, NULL);
	glShaderSource(shaderId, 1, (const GLchar**)cipa, NULL);
    glCompileShader(shaderId);
    
    GLint logLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0)
	{
        GLchar *log = new GLchar[logLength];
        glGetShaderInfoLog(shaderId, logLength, &logLength, log);
		Log::LogT("shader log: %s", log);
        delete [] log;
    }
    
	GLint status;
    glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
    if (status == 0)
	{
		glDeleteShader(shaderId);
        return 0;
    }
    
    return shaderId;
}

void Shader::LinkProgram()
{
	GLint status;
    glLinkProgram(m_programId);
    
    GLint logLength;
    glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &logLength);
    if (logLength > 0) {
        GLchar *log = new GLchar[logLength];
        glGetProgramInfoLog(m_programId, logLength, &logLength, log);
        Log::LogT("Program link log: %s", log);
        delete [] log;
    }

	glGetProgramiv(m_programId, GL_LINK_STATUS, &status);
    if (status != GL_TRUE)
	{
		assert(false);
	}
	
	ValidateProgram(m_programId);
}

bool Shader::ValidateProgram(GLuint programId)
{
	GLint logLength;
	GLint status;
    
    glValidateProgram(programId);
	glGetProgramiv(programId, GL_VALIDATE_STATUS, &status);

	if (status != GL_TRUE)
	{
		glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &logLength);
		if (logLength > 10)
		{
			GLchar *_log = new GLchar[logLength];
			glGetProgramInfoLog(programId, logLength, &logLength, _log);
			printf("validate log: %s\n", _log);
			//assert(false);
			delete _log;
		}
	}    
    
    return status == GL_TRUE;
}

uint32_t Shader::GetUniformLocation(const std::string& name) const
{
	return glGetUniformLocation(m_programId, name.c_str());
}
