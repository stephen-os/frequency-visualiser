#include <vector>
#include <iostream>

#include "imgui.h"

#include "Lumina/Core/Layer.h"
#include "Lumina/Utils/Timer.h"

#include "Lumina/Core/Aliases.h"

#include "Lumina/Renderer/Buffer.h";
#include "Lumina/Renderer/ShaderProgram.h"
#include "Lumina/Renderer/VertexArray.h"
#include "Lumina/Renderer/FrameBuffer.h"

#include <fstream>
#include <vector>
#include <cstdint>
#include <iostream>

namespace Visualiser
{
    class Visualiser : public Lumina::Layer
    {
    public:
        virtual void OnAttach() override
        {
            // Quad vertices (x, y)
            float vertices[] = {
                -1.0f, -1.0f, // bottom-left
                 1.0f, -1.0f, // bottom-right
                 1.0f,  1.0f, // top-right
                -1.0f,  1.0f  // top-left
            };

            // Indices for two triangles
            uint32_t indices[] = {
                0, 1, 2, // first triangle
                2, 3, 0  // second triangle
            };

            m_VertexBuffer = Lumina::VertexBuffer::Create(vertices, sizeof(vertices));
            Lumina::BufferLayout layout = {
                { Lumina::BufferDataType::Float2, "a_Position" }
            };
            m_VertexBuffer->SetLayout(layout);

            m_IndexBuffer = Lumina::IndexBuffer::Create(indices, 6);

            m_ShaderProgram = Lumina::ShaderProgram::Create("res/shaders/wave.vert", "res/shaders/wave.frag");

            m_VertexArray = Lumina::VertexArray::Create();
            m_VertexArray->AddVertexBuffer(m_VertexBuffer);
            m_VertexArray->SetIndexBuffer(m_IndexBuffer);

            m_FrameBuffer = Lumina::FrameBuffer::Create();
            m_FrameBuffer->Resize(800, 600);
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
            ImGui::Begin("Viewport");

            ImVec2 viewportSize = ImGui::GetContentRegionAvail();
            m_FrameBuffer->Resize((uint32_t)viewportSize.x, (uint32_t)viewportSize.y);

            m_FrameBuffer->Bind();
            m_VertexArray->Bind();
            m_ShaderProgram->Bind();

            m_ShaderProgram->SetUniformFloat("u_Time", m_TotalTimer.Elapsed());
            m_VertexArray->DrawIndexed();

            ImGui::Image((void*)(intptr_t)m_FrameBuffer->GetColorAttachment(), ImVec2(m_FrameBuffer->GetWidth(), m_FrameBuffer->GetHeight()));
            ImGui::End();

            m_ShaderProgram->Unbind();
            m_VertexArray->Unbind();
            m_FrameBuffer->Unbind();

            ImGui::Begin("FPS Counter");
            ImGui::Text("FPS: %.1f", m_FPS);
            ImGui::End();
        }

    private:
        Lumina::Shared<Lumina::VertexBuffer> m_VertexBuffer;
        Lumina::Shared<Lumina::IndexBuffer> m_IndexBuffer;
        Lumina::Shared<Lumina::ShaderProgram> m_ShaderProgram;
        Lumina::Shared<Lumina::VertexArray> m_VertexArray;
        Lumina::Shared<Lumina::FrameBuffer> m_FrameBuffer;

        Lumina::Timer m_FrameTimer;
        Lumina::Timer m_TotalTimer;
        float m_FPS = 0.0f;

        uint64_t m_UniqueID = 0;
    };
}