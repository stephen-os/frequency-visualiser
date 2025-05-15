#include "Background.h"

#include "Lumina/Renderer/RenderCommands.h"

#include "imgui.h"

namespace Visualiser
{
	Background::Background()
	{
		float vertices[] = {
			-1.0f, -1.0f, // bottom-left
			 1.0f, -1.0f, // bottom-right
			 1.0f,  1.0f, // top-right
			-1.0f,  1.0f  // top-left
		};

		uint32_t indices[] = {
			0, 1, 2, // first triangle
			2, 3, 0  // second triangle
		};

		Lumina::BufferLayout layout = {
			{ Lumina::BufferDataType::Float2, "a_Position" }
		};
 
		m_VertexBuffer = Lumina::VertexBuffer::Create(vertices, sizeof(vertices));
		m_VertexBuffer->SetLayout(layout);
		
		m_IndexBuffer = Lumina::IndexBuffer::Create(indices, 6);
		
		m_ShaderProgram = Lumina::ShaderProgram::Create("res/shaders/background.vert", "res/shaders/background.frag");

		m_VertexArray = Lumina::VertexArray::Create();
		m_VertexArray->SetVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);
	}

	void Background::Draw()
	{
		m_ShaderProgram->Bind();
		
		ImVec2 viewportSize = ImGui::GetContentRegionAvail();
		m_ShaderProgram->SetUniformVec2("u_resolution", glm::vec2(viewportSize.x, viewportSize.x));
		m_ShaderProgram->SetUniformFloat("u_gridSpacing", 40.0f);
		m_ShaderProgram->SetUniformFloat("u_thickness", 1.0f);
		m_ShaderProgram->SetUniformFloat("u_centerThickness", 2.0f);

		Lumina::RenderCommands::DrawTriangles(m_VertexArray);
		m_ShaderProgram->Unbind();
	}
}
