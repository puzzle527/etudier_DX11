#pragma once

//c++
#include <string>
#include <iostream>
#include <map>
using namespace std;

//c
#include <windows.h>
#include <time.h>
#include <assert.h>
#include <tchar.h>

//외부 라이브러리
//d3dx
#include <d3d11.h>
#include <d3dx11.h>
#include <d3dX10.h>
#include <d3dx10math.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

//Imgui
#include "imgui/imgui.h"
#include "imgui/imguiDx11.h"
#pragma comment(lib, "imgui/imgui.lib")

//fmod
#pragma comment (lib,"fmod/fmodex_vc.lib")
#include "fmod/fmod.hpp"


//매크로
#include "UserDef.h"

//내부 파일

#include "Object/Vertex.h"
#include "Util/Math.h"

#include "Object/Shader.h"
#include "Object/Object.h"

#include "Object/Line.h"
#include "Object/Rect.h"
#include "Object/Star.h"
#include "Object/Circle.h"
#include "Object/Image.h"

#include "Util/Collision.h"

#include "Scene/Scene.h"

//싱글턴
#include "Singleton/Singleton.h"
#include "Singleton/KeyManager.h"
#include "Singleton/TimeManager.h"
#include "Singleton/CamManager.h"
#include "Singleton/LightManager.h"
#include "Singleton/SceneManager.h"
#include "Singleton/SoundManager.h"
#include "Singleton/ResourceManager.h"

#define  KEYMANAGER KeyManager::GetInstance()
#define  TIMEMANAGER TimeManager::GetInstance()
#define  DeltaTime TimeManager::GetInstance()->GetElapsedTime()
#define  CAMMANAGER CamManager::GetInstance()
#define  LIGHTMANAGER LightManager::GetInstance()
#define  SCENEMANAGER SceneManager::GetInstance()
#define  SOUNDMANAGER SoundManager::GetInstance()
#define  RESOURCEMANAGER ResourceManager::GetInstance()

