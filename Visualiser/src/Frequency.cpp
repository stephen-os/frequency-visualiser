#include "Frequency.h"

#include "Lumina/Renderer/Renderer.h"
#include "Lumina/Renderer/RenderCommands.h"

#include <glm/gtc/constants.hpp>

#include <cmath>
#include "imgui.h"
#include <glad/glad.h>

namespace Visualiser
{
	Frequency::Frequency()
	{
		// Initialize vertex data
		m_Vertices.resize(m_VertexCount);

		float xStart = -1.0f;
		float xEnd = 1.0f;
		float step = (xEnd - xStart) / (m_VertexCount - 1);

		for (int i = 0; i < m_VertexCount; ++i)
		{
			float x = xStart + i * step;
			m_Vertices[i] = glm::vec2(x, 0.0f);
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

	void Frequency::Update()
	{
		float time = m_TotalTimer.Elapsed() * m_Speed;
		constexpr float pi = glm::pi<float>();

		for (int i = 0; i < m_VertexCount; ++i)
		{
			float x = m_Vertices[i].x;
			float t = m_Period * x + time;
			float y = 0.0f;

			switch (m_Type)
			{
			case SINE:
				y = sinf(t);
				break;
			case COSINE:
				y = cosf(t);
				break;
			case SQUARE:
				y = sinf(t) > 0.0f ? 1.0f : -1.0f;
				break;
			case TRIANGLE:
				y = asinf(sinf(t)) * (2.0f / pi);
				break;
			case SAWTOOTH:
				y = 2.0f * (t / (2.0f * pi) - floorf(0.5f + t / (2.0f * pi)));
				break;
			case PULSE:
				y = fmod(t, 2.0f * pi) < (2.0f * pi * m_DutyCycle) ? 1.0f : -1.0f;
				break;
			case NOISE:
				y = (static_cast<float>(std::rand()) / RAND_MAX) * 2.0f - 1.0f;
				break;
			case EXPONENTIAL:
				y = sinf(t) * expf(-fabs(x));
				break;
			case ASINE:
				y = fabs(sinf(t));
				break;
			}

			if (m_Invert)
				y = -y;

			m_Vertices[i].y = m_Amplitude * y;
		}

		m_VertexBuffer->SetData(m_Vertices.data(), m_VertexCount * sizeof(glm::vec2));
	}

	void Frequency::DrawUI()
	{
		if (ImGui::Begin("Line Settings"))
		{
			static int count = m_VertexCount;
			if (ImGui::SliderInt("Samples", &count, 2, s_MaxVertexCount))
			{
				m_VertexCount = count;
				m_Vertices.resize(m_VertexCount);

				float xStart = -1.0f;
				float xEnd = 1.0f;
				float step = (xEnd - xStart) / (m_VertexCount - 1);
				for (int i = 0; i < m_VertexCount; ++i)
				{
					float x = xStart + i * step;
					m_Vertices[i] = glm::vec2(x, 0.0f);
				}

				m_VertexBuffer->SetData(m_Vertices.data(), m_VertexCount * sizeof(glm::vec2));
			}

			const char* waveNames[] = 
			{
				"Sine", "Cosine", "Square", "Triangle", "Sawtooth",
				"Pulse", "Noise", "Exponential", "Abs Sine"
			};
			int current = static_cast<int>(m_Type);
			if (ImGui::Combo("Type", &current, waveNames, IM_ARRAYSIZE(waveNames)))
			{
				m_Type = static_cast<FrequencyType>(current);
			}

			ImGui::Checkbox("Invert", &m_Invert);
			ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 10.0f);
			ImGui::SliderFloat("Amplitude", &m_Amplitude, 0.0f, 1.0f);
			ImGui::SliderFloat("Period", &m_Period, 1.0f, 50.0f);
			ImGui::SliderFloat("Thickness", &m_Thickness, 0.01f, 10.0f, "%.4f");
			ImGui::ColorEdit3("Color", &m_Color[0]);

			if (m_Type == PULSE)
				ImGui::SliderFloat("Duty Cycle", &m_DutyCycle, 0.01f, 0.99f);
		}
		ImGui::End();
	}

	void Frequency::Draw()
	{
		m_LineShader->Bind();
		m_LineShader->SetUniformVec3("u_Color", m_Color);
		// glEnable(GL_LINE_SMOOTH);
		glLineWidth(m_Thickness);
		Lumina::RenderCommands::DrawLineStrips(m_VertexArray, m_VertexCount);
	}
}
