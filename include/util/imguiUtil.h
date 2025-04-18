#pragma once

#include "imgui.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

#include "window.h"
#include "shader.h"

#include <string>
#include <map>

namespace UTIL{
    class ImguiUtil {
    private:
        ImGuiIO* _io;

        const GLchar* _fragSource;

        std::map<const char*, float> _fragMap = {
            {"{{GAMMA}}", 1.8}, {"{{SPEC_STRENGTH}}", 0.5}, {"{{SHINE_FACTOR}}", 64},
            {"{{AMBIENT_STRENGTH}}", 0.1}, {"{{AMBIENT_BLEND}}", 0.2}
        };



    public:
        ImguiUtil() {
            IMGUI_CHECKVERSION();
            ImGui::CreateContext();

            _io = &ImGui::GetIO();

            _io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
            _io->ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;
        }

        ~ImguiUtil() {
            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL2_Shutdown();
            ImGui::DestroyContext();
            delete[] _fragSource;
        }

        void init(DISPLAY::Window *window) {
            ImGui_ImplSDL2_InitForOpenGL(window->getWindow(), window->getContext());
            ImGui_ImplOpenGL3_Init("#version 460");

            _fragSource = UTIL::fileReader("shaders/templates/shader.frag");
            std::string filled = replaceFragVars(_fragSource);
            fileSaver("shaders/shader.frag", (char*)filled.c_str());
        }

        void begin() {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();
        }

        void fragBox(glm::ivec2 pos, glm::ivec2 size, DISPLAY::Shader* shader) {
            static int shineIndex = 6;

            ImGui::Begin("shader.frag", 0, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar);

            ImGui::SetWindowPos(ImVec2(pos.x, pos.y));
            ImGui::SetWindowSize(ImVec2(size.x, size.y));

            float fullWidth = ImGui::GetContentRegionAvail().x;

            ImGui::Text("shader.frag");
            ImGui::Spacing();

            ImGui::Text("GAMMA FACTOR:");
            ImGui::SetNextItemWidth(fullWidth);
            ImGui::SliderFloat("##GAMMA", &_fragMap.at("{{GAMMA}}"), 0.0f, 3.2f);
            ImGui::Spacing();

            ImGui::Text("SPEC STRENGTH:");
            ImGui::SetNextItemWidth(fullWidth);
            ImGui::SliderFloat("##SPEC_STRENGTH", &_fragMap.at("{{SPEC_STRENGTH}}"), 0.0f, 1.0f);
            ImGui::Spacing();

            ImGui::Text("SHINE FACTOR:");
            ImGui::SetNextItemWidth(fullWidth);
            if (ImGui::SliderInt("##SHINE", &shineIndex, 0, 9, std::to_string(1 << shineIndex).c_str())) {
                _fragMap.at("{{SHINE_FACTOR}}") = (float)(1 << shineIndex);
            }
            ImGui::Spacing();

            ImGui::Text("AMBIENT STRENGTH:");
            ImGui::SetNextItemWidth(fullWidth);
            ImGui::SliderFloat("##AMBIENT_STRENGTH", &_fragMap.at("{{AMBIENT_STRENGTH}}"), 0.0f, 1.0f);
            ImGui::Spacing();

            ImGui::Text("AMBIENT BLEND:");
            ImGui::SetNextItemWidth(fullWidth);
            ImGui::SliderFloat("##AMBIENT_BLEND", &_fragMap.at("{{AMBIENT_BLEND}}"), 0.0f, 1.0f);
            ImGui::Spacing();

            
            float buttonWidth = (fullWidth - ImGui::GetStyle().ItemSpacing.x) * 0.5f;

            ImGui::SetNextItemWidth(buttonWidth);
            if (ImGui::Button("Test", ImVec2(buttonWidth, 0))) {
                std::string filled = replaceFragVars(_fragSource);
                shader->testFrag((const GLchar*)filled.c_str());
            }

            ImGui::SameLine();
            ImGui::SetNextItemWidth(buttonWidth);
            if (ImGui::Button("Save", ImVec2(buttonWidth, 0))) {
                std::string filled = replaceFragVars(_fragSource);
                fileSaver("shaders/shader.frag", (char*)filled.c_str());
            
                shader->reloadFrag("shaders/shader.frag");
            }

            ImGui::End();
        }

        std::string replaceFragVars(std::string src) {
            for (const auto &[var, val] : _fragMap)
                src.replace(src.find(var), strlen(var), std::to_string(val));
            return src;
        }

        void end() {
            ImGui::Render();
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        bool isCaptured() {return _io->WantCaptureKeyboard;}
        bool isHovering() {return _io->WantCaptureMouse;}

    };
}