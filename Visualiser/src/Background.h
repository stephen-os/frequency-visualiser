#pragma once

#include "Lumina/Core/Aliases.h"

#include "Lumina/Renderer/Buffer.h"
#include "Lumina/Renderer/ShaderProgram.h"
#include "Lumina/Renderer/VertexArray.h"

namespace Visualiser
{
	class Background
	{
	public: 
		Background();
		~Background() = default;

		void Draw();
	private:
		Lumina::Shared<Lumina::VertexBuffer> m_VertexBuffer;
		Lumina::Shared<Lumina::IndexBuffer> m_IndexBuffer;
		Lumina::Shared<Lumina::ShaderProgram> m_ShaderProgram;
		Lumina::Shared<Lumina::VertexArray> m_VertexArray;
	};
}