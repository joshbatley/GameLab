#include "Panel.h"

void SetupPanel(Engine::World &_, Event::Handler &eventHandler, Engine::Resource<Data> data)
{
    auto &d = data.extract<Data>();
    ImGui::SetNextWindowSize(ImVec2(400, 768));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    ImGui::Begin("Another Window", nullptr, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse);
    ImGui::Text("Hello from another window!");

    int vec[2] = {d.size.x, d.size.y};
    if (ImGui::DragInt2("BoxSize", vec, 32, 32, 1024)) {
        d.size = {vec[0], vec[1]};
        eventHandler.Send(UpdateBoxSize {{vec[0], vec[1]}, d.pos});
    }

    int vec2[2] = {d.pos.x, d.pos.y};
    if (ImGui::DragInt2("BoxPos", vec2, 32, 0, 1024)) {
        d.pos = {vec2[0], vec2[1]};
        eventHandler.Send(UpdateBoxSize {d.size, {vec2[0], vec2[1]}});
    }

    ImGui::End();
}
