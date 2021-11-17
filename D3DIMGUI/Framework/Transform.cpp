#include "Framework.h"
#include "Transform.h"

Transform::Transform()//: scale(1.0f, 1.0f, 1.0f)
{
    //scale.x = 1.0f;
    //scale.y = 1.0f;
    //scale.z = 1.0f;
    //scale.x = scale.y = scale.z = 1.0f;
    scale = Vector3(1.0f, 1.0f, 1.0f);
}

void Transform::ImGuiRender()
{
    //rot,scale,pos
    //float a[3];
    ImGui::InputFloat3("Pos", (float*)&position);
    ImGui::InputFloat3("Scale", (float*)&rotation);
    ImGui::InputFloat3("Rot", (float*)&scale);
}
