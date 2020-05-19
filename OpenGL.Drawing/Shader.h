#pragma once

#include <gl/glew.h>
#include <string>

namespace GL
{
	class Shader
	{
	public:
		Shader() = default;

		void Load(std::string&& vertexPath, std::string&& fragmentPath);
		void Use();

		constexpr int ShaderId() { return m_ShaderId; }

	private:
		GLuint m_ShaderId;
		GLuint m_VertexShader;
		GLuint m_FragmentShader;

		GLuint LoadVertexShader(std::string&& vertexPath);
		GLuint LoadFragmentShader(std::string&& fragmentPath);
		std::string ReadShader(std::string&& filename);
		bool HasCompiled(GLuint shader);
	};
}