#include "stdafx.h"
#include "Scene2.h"

//�༺�� �������� �����ӿ� ������ �ȹ޵���
//�����̽��� ������ �¾��� �� 2�ʰ��� ȸ��

HRESULT Scene2::Init()
{
    rc1 = new Rect(Vector2(0.5f, 0.0f));
    rc1->Init();
    rc1->Position = Vector2(400.0f, 400.0f);
    rc1->Scale = Vector2(100.0f, 200.0f);

    rc2 = new Rect(Vector2(-0.5f, 0.0f));
    rc2->Init();
    rc2->Position = Vector2(100.0f, 100.0f);
    rc2->Scale = Vector2(200.0f, 100.0f);


    return S_OK;
}

void Scene2::Release()
{
    delete rc1;
    delete rc2;
}

void Scene2::Update()
{
    if(KEYMANAGER->KeyPress('W'))
    {
        rc1->Position += UP * 100.0f * DeltaTime;
    }
    if(KEYMANAGER->KeyPress('S'))
    {
        rc1->Position += DOWN * 100.0f * DeltaTime;
    }

    if(KEYMANAGER->KeyPress('A'))
    {
        rc1->Position += LEFT * 100.0f * DeltaTime;
    }
    //������ȸ��
    if(KEYMANAGER->KeyPress('D'))
    {
        rc1->Position += RIGHT * 100.0f * DeltaTime;
    }

    //�浹�� ���尪 ����
    rc1->WorldUpdate();
    rc2->WorldUpdate();
}

void Scene2::LateUpdate()
{
   //�浹 üũ

    if (AABB(rc1, rc2))
    {
        cout << TIMEMANAGER->GetWorldTime() << endl;
    }

}

void Scene2::Render()
{
    rc1->Render();
    rc2->Render();
}
