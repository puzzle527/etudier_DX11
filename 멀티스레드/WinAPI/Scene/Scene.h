#pragma once
#include "stdafx.h"
//�������̽�, �߻�ȭŬ����
class Scene
{
public:
    Scene(){};//����
    virtual ~Scene(){};//�Ҹ�
    //���� ���� �Լ�
    //�ݵ�� �ڽĿ��� �������ؾ���
    virtual HRESULT Init() = 0;//�ʱ�ȭ
    virtual void Release() = 0;//����

    //����
    virtual void Update() = 0;//����
    virtual void LateUpdate() = 0;//��������
    virtual void Render() = 0;//�׸���
    virtual void TextRender() = 0;//�׸���
};