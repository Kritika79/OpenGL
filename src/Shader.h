#pragma once 
#include <string>
#include <unordered_map>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendrerID;
	std::unordered_map<std::string,int> m_UniformLocationCache;
public:
	Shader(const std::string& fielpath);
	~Shader();

	void Bind() const;
	void Unbind() const;


	//set unifroms
	void SetUniform1i(const std::string& name,int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUnifrom4f(const std::string& name, float v0, float v1, float v2, float v3);
private:
	  ShaderProgramSource ParseShader(const std::string& filepath);
	int CreateShader(const std::string& vertexshader, const std::string& fragmentshader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	 int GetUniformLocation(const std::string& name);

};