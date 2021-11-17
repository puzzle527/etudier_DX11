#pragma once
#include "stdafx.h"
//인터페이스, 추상화클래스
class Scene
{
public:
    Scene(){};//생성
    virtual ~Scene(){};//소멸
    //순수 가상 함수
    //반드시 자식에서 재정의해야함
    virtual HRESULT Init() = 0;//초기화
    virtual void Release() = 0;//해제

    //루프
    virtual void Update() = 0;//갱신
    virtual void LateUpdate() = 0;//늦은갱신
    virtual void Render() = 0;//그리기
    virtual void TextRender() = 0;//그리기
};