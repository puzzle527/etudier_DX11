#pragma once
#include "targetver.h"
// 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#define WIN32_LEAN_AND_MEAN 
// Windows 헤더 파일
//WinAPI 포함

#define PI          3.141592f //원주율
#define TORADIAN	0.017453f //pi/180 의값
#define TODEGREE	57.295779f//180/pi 의값


#include <string>
#include <iostream>


#include <windows.h>
#include <time.h>
#include <assert.h>
// C 런타임 헤더 파일입니다.
#include <tchar.h> //제네릭 텍스트 매핑
//멀티바이트 유니코드 스위치
using namespace std;

//#ifdef _DEBUG
#ifdef _MBCS
#define _tstring string
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#define _tstring wstring
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#endif
//#endif

//dx 라이브러리 추가
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


typedef D3DXVECTOR2 Vector2; //x,y
typedef D3DXVECTOR3 Vector3;//x,y,z
typedef D3DXVECTOR4 Vector4;//x,y,z,w
typedef D3DXMATRIX	Matrix;
typedef D3DXCOLOR	Color;
#define UP Vector2(0.0f,1.0f)
#define DOWN Vector2(0.0f,-1.0f)
#define LEFT Vector2(-1.0f,0.0f)
#define RIGHT Vector2(1.0f,0.0f)
#define Length(p) D3DXVec2Length(p)

//오브젝트
#include "Object/Vertex.h"
#include "Util/Math.h"

using namespace Vertex;
#include "Object/Shader.h"
#include "Object/Object.h"

#include "Object/Line.h"
#include "Object/Rect.h"
#include "Object/Star.h"
#include "Object/Circle.h"
#include "Object/Image.h"

#include "Util/Collision.h"

//씬
#include "Scene/Scene.h"
#include "Scene/Scene1.h"
#include "Scene/Scene2.h"

//싱글턴
#include "Singleton/Singleton.h"
#include "Singleton/KeyManager.h"
#include "Singleton/TimeManager.h"
#include "Singleton/CamManager.h"

#define  KEYMANAGER KeyManager::GetInstance()
#define  TIMEMANAGER TimeManager::GetInstance()
#define  DeltaTime TimeManager::GetInstance()->GetElapsedTime()
#define  CAMMANAGER CamManager::GetInstance()

//해상도 관련
//창 시작좌표
#define     WINSTARTX 0
#define     WINSTARTY 0
//창 너비,높이 (디스플레이크기,해상도에따라 변경된다)
#define     WINSIZEX 800
#define     WINSIZEY 600

//고정프레임
#define     FIXFRAME 100


//매크로 함수
#define     SAFE_DELETE(p) {delete p;  p = nullptr;}
#define     SAFE_DELETE_ARRAY(p) {delete[] p;  p = nullptr;}
#define     SAFE_RELEASE(p)  {if(p){(p)->Release(); (p)=nullptr;}}


//다른 외부파일도 선언된 전역변수를 쓸때

extern HWND                         g_hwnd;
extern Vector2                      g_Mouse;
extern IDXGISwapChain*				g_SwapChain;
extern ID3D11Device*				g_Device;
extern ID3D11DeviceContext*			g_DeviceContext;
extern ID3D11RenderTargetView*		g_RTV;