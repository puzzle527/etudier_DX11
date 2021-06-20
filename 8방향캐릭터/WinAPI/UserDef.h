#pragma once

//macro
#define PI          3.141592f //원주율
#define TORADIAN	0.017453f //pi/180 의값
#define TODEGREE	57.295779f//180/pi 의값

#ifdef _MBCS
#define _tstring string
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#else
#define _tstring wstring
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console") 
#endif
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
#define MAKEGET(Type, Value)	\
	Type Get##Value(){return Value;} 
#define MAKESET(Type, Value)	\
	void Set##Value(Type val){Value = val;}
#define MAKEGETSET(Type, Value) \
	MAKEGET(Type, Value) MAKESET(Type, Value)



//매크로 함수
#define     SAFE_DELETE(p) {delete p;  p = nullptr;}
#define     SAFE_DELETE_ARRAY(p) {delete[] p;  p = nullptr;}
#define     SAFE_RELEASE(p)  {if(p){(p)->Release(); (p)=nullptr;}}


//다른 외부파일도 선언된 전역변수를 쓸때

extern HWND                         g_hwnd;
extern Vector2                      g_Mouse;
extern IDXGISwapChain* g_SwapChain;
extern ID3D11Device* g_Device;
extern ID3D11DeviceContext* g_DeviceContext;
extern ID3D11RenderTargetView* g_RTV;
extern ID3D11BlendState* g_BlendState[2];
