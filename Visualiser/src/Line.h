#pragma once

#include "Lumina/Core/Aliases.h"
#include "Lumina/Renderer/Buffer.h"
#include "Lumina/Renderer/ShaderProgram.h"
#include "Lumina/Renderer/VertexArray.h"
#include "Lumina/Utils/Timer.h"
#include "glm/glm.hpp"
#include <vector>

namespace Visualiser
{
	class Line
	{
	public:
		Line();
		~Line() = default;

		void DrawUI();
		void Draw();
		void Update();

	private:
		Lumina::Shared<Lumina::VertexBuffer> m_VertexBuffer;
		Lumina::Shared<Lumina::VertexArray> m_VertexArray;
		Lumina::Shared<Lumina::ShaderProgram> m_LineShader;

		Lumina::Timer m_TotalTimer;

		std::vector<glm::vec2> m_Vertices;

		static constexpr int s_VertexCount = 800;
	};
}
