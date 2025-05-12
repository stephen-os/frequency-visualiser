#include "Frequency.h"

#include "imgui.h"

namespace Visualiser
{
	Frequency::Frequency()
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

		m_SineShader = Lumina::ShaderProgram::Create("res/shaders/wave.vert", "res/shaders/sine.frag");
		m_CosineShader = Lumina::ShaderProgram::Create("res/shaders/wave.vert", "res/shaders/cosine.frag");
		m_SquareShader = Lumina::ShaderProgram::Create("res/shaders/wave.vert", "res/shaders/square.frag");
		m_TriangleShader = Lumina::ShaderProgram::Create("res/shaders/wave.vert", "res/shaders/triangle.frag");
		m_SawToothShader = Lumina::ShaderProgram::Create("res/shaders/wave.vert", "res/shaders/saw_tooth.frag");

		m_DrawShader = m_SineShader; 

		m_VertexArray = Lumina::VertexArray::Create();
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

	}

	void Frequency::DrawUI()
	{
		ImGui::Begin("Frequency Controls");

		ImGui::SliderFloat("Amplitude", &m_Amplitude, 0.0f, 1.0f, "%.2f");
		ImGui::SliderFloat("Period", &m_Period, 1.0f, 50.0f, "%.2f");
		ImGui::SliderFloat("Thickness", &m_Thickness, 0.001f, 0.05f, "%.3f");
		ImGui::ColorEdit3("Wave Color", &m_Color[0]);
		ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 10.0f, "%.2f");

		const char* waveTypes[] = { "Sine", "Cosine", "Square", "Triangle", "Sawtooth" };
		int current = static_cast<int>(m_CurrentWave);
		if (ImGui::Combo("Wave Type", &current, waveTypes, IM_ARRAYSIZE(waveTypes)))
		{
			m_CurrentWave = static_cast<WaveType>(current);

			switch (m_CurrentWave)
			{
			case WaveType::Sine:     m_DrawShader = m_SineShader; break;
			case WaveType::Cosine:   m_DrawShader = m_CosineShader; break;
			case WaveType::Square:   m_DrawShader = m_SquareShader; break;
			case WaveType::Triangle: m_DrawShader = m_TriangleShader; break;
			case WaveType::Sawtooth: m_DrawShader = m_SawToothShader; break;
			}
		}

		ImGui::End();
	}

	void Frequency::Draw()
	{
		m_VertexArray->Bind();
		float time = m_TotalTimer.Elapsed() * m_Speed;
		
		m_DrawShader->Bind();
		m_DrawShader->SetUniformFloat("u_Time", time);
		m_DrawShader->SetUniformFloat("u_Amplitude", m_Amplitude);
		m_DrawShader->SetUniformFloat("u_Period", m_Period);
		m_DrawShader->SetUniformFloat("u_Thickness", m_Thickness);
		m_DrawShader->SetUniformVec3("u_Color", m_Color);

		m_VertexArray->DrawIndexed();

		m_VertexArray->Unbind();
		m_DrawShader->Unbind();
	}
}