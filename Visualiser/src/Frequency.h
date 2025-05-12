#pragma once

#include "Lumina/Core/Aliases.h"

#include "Lumina/Renderer/Buffer.h"
#include "Lumina/Renderer/ShaderProgram.h"
#include "Lumina/Renderer/VertexArray.h"


#include "Lumina/Utils/Timer.h"

#include "glm/glm.hpp"

namespace Visualiser
{
	enum class WaveType
	{
		Sine = 0,
		Cosine,
		Square,
		Triangle,
		Sawtooth
	};

	class Frequency
	{
	public:
		Frequency();
		~Frequency() = default;
		void DrawUI();
		void Draw();
	private:
		Lumina::Shared<Lumina::VertexBuffer> m_VertexBuffer;
		Lumina::Shared<Lumina::IndexBuffer> m_IndexBuffer;
		Lumina::Shared<Lumina::VertexArray> m_VertexArray;

		// Shaders
		Lumina::Shared<Lumina::ShaderProgram> m_SineShader;
		Lumina::Shared<Lumina::ShaderProgram> m_CosineShader;
		Lumina::Shared<Lumina::ShaderProgram> m_SquareShader;
		Lumina::Shared<Lumina::ShaderProgram> m_TriangleShader;
		Lumina::Shared<Lumina::ShaderProgram> m_SawToothShader;

		WaveType m_CurrentWave = WaveType::Sine;
		Lumina::Shared<Lumina::ShaderProgram> m_DrawShader;

		float m_Speed = 1.0f;
		float m_Amplitude = 0.4f;
		float m_Period = 10.0f;
		float m_Thickness = 0.01f;
		glm::vec3 m_Color = { 0.0f, 1.0f, 0.0f };

		Lumina::Timer m_TotalTimer;
	};
}