#include "Line.h"

#include "Lumina/Renderer/Renderer.h"
#include "Lumina/Renderer/RenderCommands.h"

#include <cmath>

namespace Visualiser
{
	Line::Line()
	{
		// Initialize sine wave vertex data
		m_Vertices.resize(s_VertexCount);

		float xStart = -1.0f;
		float xEnd = 1.0f;
		float step = (xEnd - xStart) / (s_VertexCount - 1);

		for (int i = 0; i < s_VertexCount; ++i)
		{
			float x = xStart + i * step;
			m_Vertices[i] = glm::vec2(x, 0.0f); // Start with y = 0, animate later
		}

		Lumina::BufferLayout layout = {
			{ Lumina::BufferDataType::Float2, "a_Position" }
		};

		m_VertexBuffer = Lumina::VertexBuffer::Create(m_Vertices.data(), m_Vertices.size() * sizeof(glm::vec2));
		m_VertexBuffer->SetLayout(layout);

		m_VertexArray = Lumina::VertexArray::Create();
		m_VertexArray->SetVertexBuffer(m_VertexBuffer);

		m_LineShader = Lumina::ShaderProgram::Create("res/shaders/line.vert", "res/shaders/line.frag");
	}

	void Line::Update()
	{
		float time = m_TotalTimer.Elapsed();

		for (int i = 0; i < s_VertexCount; ++i)
		{
			float x = m_Vertices[i].x;
			m_Vertices[i].y = 0.3f * sinf(5.0f * x + time); // Adjustable wave
		}

		m_VertexBuffer->SetData(m_Vertices.data(), m_Vertices.size() * sizeof(glm::vec2));
	}

	void Line::DrawUI()
	{
		// Optional ImGui logic (if needed)
	}

	void Line::Draw()
	{
		m_LineShader->Bind();
		Lumina::RenderCommands::DrawLineStrips(m_VertexArray, s_VertexCount);
	}
}
