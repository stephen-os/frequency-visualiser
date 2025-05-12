#include <vector>
#include <iostream>

#include "imgui.h"

#include "Lumina/Core/Layer.h"
#include "Lumina/Utils/Timer.h"

#include "Lumina/Core/Aliases.h"

#include "Lumina/Renderer/FrameBuffer.h"

#include "Background.h"
#include "Frequency.h"

#include <fstream>
#include <cstdint>

namespace Visualiser
{
    class Visualiser : public Lumina::Layer
    {
    public:
        virtual void OnAttach() override
        {
			m_FrameBuffer = Lumina::FrameBuffer::Create();
        }

        virtual void OnDetach() override
        {

        }

        virtual void OnUpdate(float timestep) override
        {
            float elapsedTime = m_FrameTimer.Elapsed();
            m_FPS = 1.0f / elapsedTime;
            m_FrameTimer.Reset();
        }

        virtual void OnUIRender() override
        {
			m_Frequency.DrawUI();

            ImGui::Begin("Viewport");

            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            m_FrameBuffer->Bind();
            m_FrameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);

            m_Background.Draw();
			m_Frequency.Draw();

            ImGui::Image((void*)(intptr_t)m_FrameBuffer->GetColorAttachment(), ImVec2(m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight()));
            ImGui::End();

            m_FrameBuffer->Unbind();

            ImGui::Begin("FPS Counter");
            ImGui::Text("FPS: %.1f", m_FPS);
            ImGui::End();
        }

    private:
		Background m_Background;
		Frequency m_Frequency;

        Lumina::Shared<Lumina::FrameBuffer> m_FrameBuffer;

        Lumina::Timer m_FrameTimer;
        Lumina::Timer m_TotalTimer;
        float m_FPS = 0.0f;

        uint64_t m_UniqueID = 0;
    };
}