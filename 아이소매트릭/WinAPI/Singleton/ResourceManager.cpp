#include "stdafx.h"
#include "ResourceManager.h"

ResourceManager::ResourceManager()
{
    {
        //정점 서술
        D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
        {
            { "POSITION",//시멘틱에서 정의한 자료형
            0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
            DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
            0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
            0,//이 요소가 메모리덩어리 시작지점부터 얼마나 떨어진 위치에 있는가를 알려준다.처음시작0
            D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
            0 },//넘어가기
        { "COLOR",//시멘틱에서 정의한 자료형
        0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
        DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
        0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
        12,//포지션 R32G32B32 4 ,4,4 ->12
        D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
        0 }
        };

        ShaderArray[0] = new Shader(_T("./Shader/1.Basic.hlsl"));
        UINT ElementCount = ARRAYSIZE(LayoutDesc);
        ShaderArray[0]->CreateInputLayout(LayoutDesc, ElementCount);
    }
    {
        //정점 서술
        D3D11_INPUT_ELEMENT_DESC LayoutDesc[] =
        {
            { "POSITION",//시멘틱에서 정의한 자료형
            0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
            DXGI_FORMAT_R32G32B32_FLOAT,//3개의 32비트 float설정
            0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
            0,//이 요소가 메모리덩어리 시작지점부터 얼마나 떨어진 위치에 있는가를 알려준다.처음시작0
            D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
            0 },//넘어가기
            { "UV",//시멘틱에서 정의한 자료형
            0,//시멘틱에서 정의한 인덱스 0으로 지정했기에 0 사용
            DXGI_FORMAT_R32G32_FLOAT,//3개의 32비트 float설정
            0,//0~15사이의 인덱스 지정, 동시에 15개까지 버퍼가 입력슬롯을 가질수있다.
            12,//포지션 R32G32B32 4 ,4,4 ->12
            D3D11_INPUT_PER_VERTEX_DATA,//넘어가기
            0 }
        };

        ShaderArray[1] = new Shader(_T("./Shader/2.Image.hlsl"));
        UINT ElementCount = ARRAYSIZE(LayoutDesc);
        ShaderArray[1]->CreateInputLayout(LayoutDesc, ElementCount);
    }
}

ResourceManager::~ResourceManager()
{
    SAFE_DELETE(ShaderArray[0]);
    SAFE_DELETE(ShaderArray[1]);
    for (auto i = SrvMap.begin();
        i != SrvMap.end(); i++)
    {
        if (i->second)
        {
            i->second->Release();
        }
    }
    SrvMap.clear();
}

ID3D11ShaderResourceView* ResourceManager::LoadTexture(_tstring file)
{
    if (SrvMap.find(file) != SrvMap.end())
        return SrvMap[file];


    _tstring textureFile = _T("./Images/") + file;

    HRESULT hr;
    ID3D11ShaderResourceView* temp;

    //jpg,png,gif,bmp 정도는 불러올수있음
    D3DX11CreateShaderResourceViewFromFile
    (
        g_Device,//디바이스
        textureFile.c_str(),//파일이름
        NULL, //추가적인 이미지 정보 NULL값은 원본크기
        NULL,//널값
        &temp,//쉐이더자원뷰
        &hr
    );
    assert(SUCCEEDED(hr) && "텍스쳐로드 실패");

    SrvMap[file] = temp;
    return temp;
}
