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
	enum FrequencyType
	{
		SINE = 0,
		COSINE,
		SQUARE,
		TRIANGLE,
		SAWTOOTH,
		PULSE,
		NOISE,
		EXPONENTIAL,
		ASINE, 
	};

	class Frequency
	{
	public:
		Frequency();
		~Frequency() = default;

		void DrawUI();
		void Draw();
		void Update();

	private:
		Lumina::Shared<Lumina::VertexBuffer> m_VertexBuffer;
		Lumina::Shared<Lumina::VertexArray> m_VertexArray;
		Lumina::Shared<Lumina::ShaderProgram> m_LineShader;

		Lumina::Timer m_TotalTimer;

		std::vector<glm::vec2> m_Vertices;

		float m_Speed = 1.0f;
		float m_Amplitude = 0.4f;
		float m_Period = 10.0f;
		float m_Thickness = 0.01f;
		glm::vec3 m_Color = { 0.0f, 1.0f, 0.0f };

		int m_VertexCount = 300;
		static constexpr int s_MaxVertexCount = 600;

		FrequencyType m_Type = SINE;
		float m_DutyCycle = 0.5f;
		bool m_Invert = false;
	};
}
