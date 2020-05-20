#pragma once

#include <gl/glew.h>

namespace GL
{
	class Model
	{
	public:
		Model() = default;
		virtual ~Model() = default;

		void Load();
		void Render();

	private:
		GLuint m_VertexArrayObject;
		GLuint m_VertexBuffer;
		GLuint m_IndexBuffer;
	};
}