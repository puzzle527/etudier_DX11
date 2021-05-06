#pragma once
#include "stdafx.h"
//순수가상함수로 이루어진 클래스
//추상화클래스 인터페이스
class Scene
{
public:
    Scene(){};//생성
    virtual ~Scene(){};//소멸

    //순수 가상함수
    //자식클래스에서 반드시 재정의해야하는 함수
    virtual HRESULT Init() = 0;//초기화
    virtual void Release() = 0;//해제
    //루프
    virtual void Update() = 0;//갱신
    virtual void LateUpdate() = 0;//늦은갱신
    virtual void Render() = 0;//그리기
};
