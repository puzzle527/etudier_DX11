#pragma once
#include "stdafx.h"
//���������Լ��� �̷���� Ŭ����
//�߻�ȭŬ���� �������̽�
class Scene
{
public:
    Scene(){};//����
    virtual ~Scene(){};//�Ҹ�

    //���� �����Լ�
    //�ڽ�Ŭ�������� �ݵ�� �������ؾ��ϴ� �Լ�
    virtual HRESULT Init() = 0;//�ʱ�ȭ
    virtual void Release() = 0;//����
    //����
    virtual void Update() = 0;//����
    virtual void LateUpdate() = 0;//��������
    virtual void Render() = 0;//�׸���
};
