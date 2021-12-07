#pragma once

#include <Windows.h>
#include <assert.h>

//STL
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <functional>
#include <iterator>
#include <thread>
#include <mutex>
using namespace std;

#define Check(hr) { assert(SUCCEEDED(hr)); }
#define Super __super

#define SafeRelease(p){ if(p){ (p)->Release(); (p) = NULL; } }
#define SafeDelete(p){ if(p){ delete (p); (p) = NULL; } }
#define SafeDeleteArray(p){ if(p){ delete [] (p); (p) = NULL; } }


//DirectX d3d 11
#include <d3d11.h>
#include <dxgi1_2.h>
#include <d3dcompiler.h>
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#pragma comment(lib, "dxgi.lib")
//#pragma comment(lib, "dxguid.lib")


//DirectXTk 
#include "../Libs/DirectXTK/DDSTextureLoader.h"
#include "../Libs/DirectXTK/WICTextureLoader.h"
#include "../Libs/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

#pragma comment (lib,"../Libs/DirectXTK/DirectXTK.lib")

//Imgui
#include "../Libs/ImGui/imgui.h"
#include "../Libs/ImGui/imgui_impl_dx11.h"
#include "../Libs/ImGui/imgui_impl_win32.h"
#pragma comment(lib, "../Libs/ImGui/ImGuiL.lib")

#include "Types.h"
#include "Window.h"
#include "D3d.h"
#include "Gui.h"

#include "String.h"
#include "BinaryFile.h"

#include "VertexType.h"
#include "Transform.h"
#include "Mesh.h"
#include "Shader.h"
#include "GameObject.h"
#include "Camera.h"
#include "ResourceManager.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Timer.h"
//Framework .Lib
#pragma comment (lib,"../Libs/FrameWork/FrameWork.lib")

#define  D3D          D3d::GetInstance()
#define  GUI          Gui::GetInstance()
#define  RESOURCE	  ResourceManager::GetInstance()
#define  KEYBOARD	  Keyboard::GetInstance()
#define  MOUSE	      Mouse::GetInstance()
#define  TIMER	      Timer::GetInstance()
#define  DELTA        Timer::GetInstance()->GetDeltaTime()