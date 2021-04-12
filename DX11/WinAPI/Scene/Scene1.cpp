#include "stdafx.h"
#include "Scene1.h"

//���� ���׸���
//ȸ���̵�ũ�� ��ȯ ����

HRESULT Scene1::Init()
{


    //�߽����� -0.5f��ŭ �̵�
    rc = new Rect();
    rc->Init();
    rc->Position = Vector2(200, 300);
    rc->Rotation = 0.0f;
    rc->Scale = Vector2(100, 100);
    rc->isAxis = true;

    child = new Rect();
    child->Init();
    child->Position = Vector2(100, 100);
    child->Rotation = 0.0f;
    child->Scale = Vector2(50, 50);
    child->isAxis = true;
    //���ϵ尴ü�� �θ������ rc�� ȸ���̵����
    child->P = &rc->RT;

    child2 = new Rect();
    child2->Init();
    child2->Position = Vector2(70, 70);
    child2->Rotation = 0.0f;
    child2->Scale = Vector2(30, 30);
    child2->isAxis = true;
    //����2�尴ü�� �θ������ rc�� ȸ���̵����
    child2->P = &child->RT;


    //�׷����Ѿ��� 30ũ��θ� ����
    ln = new Object();
    ln->Init();
    ln->Scale.x = 30.0f;
    ln->Scale.y = 30.0f;
    ln->isAxis = true;

    lnChild = new Circle(3);
    lnChild->Init();
    lnChild->Position = Vector2(30.0f,0.0f);
    lnChild->Scale.x = 30.0f;
    lnChild->Scale.y = 30.0f;
    lnChild->P = &ln->RT;

    //lnChild->isAxis = true;

    rcSpeed = 000.0f;

    return S_OK;
    //return E_FAIL;
}

void Scene1::Release()
{
    
    delete rc;
    delete ln;
    delete child;
    delete child2;
    delete lnChild;
}

void Scene1::Update()
{

    // & | ^ ��Ʈ������
    //�̵�
    if(KEYMANAGER->KeyPress('W'))
    {

        //���-> ���ӵ��� �����Ѱ�

        //�ʴ� 100�ӵ� ����
        //�ӵ�    ���ӵ�
        rcSpeed += DeltaTime * 200.0f;

        //�ʴ� 100�ȼ���ŭ �̵�
        rc->Position +=
            rc->Right * DeltaTime * rcSpeed;
    }
    if(KEYMANAGER->KeyPress('S'))
    {
        rc->Position -=
            rc->Right * DeltaTime * 100.0f;
    }
    rc->Rotation =
        DirToRadian(g_Mouse - rc->Position);
    //�ݽð�ȸ��
    //if(KEYMANAGER->KeyPress('A'))
    //{
    //   rc->Rotation -=0.1f;
    //}
    ////�ð����ȸ��
    //if(KEYMANAGER->KeyPress('D'))
    //{
    //    rc->Rotation += 0.1f;
    //}
    if(KEYMANAGER->KeyDown(VK_LBUTTON))
    {
        //�ѹ߾��߻�
        for(int i = 0; i < BULLETMAX; i++)
        {
            //�߻�ȳ��� �Ÿ��� �߻�ȵȳ��� ã��
            if(bl[i].isFire)continue;

            //�߻���̶�� �����
            bl[i].isFire = true;
            bl[i].Pos = rc->Position;
            bl[i].Dir = rc->Right;
            bl[i].Rot = 0.0f;
            //1�ʴ� 0������
            bl[i].Speed = -200.0f;
            //bl[i].Rot = rc->Rotation;
            break;//�ѹ߸������ؼ� �ݺ��� Ż��
        }
    }
    
    //�߻�� �Ѿ��� ���ư��� �ϱ�
    for(int i = 0; i < BULLETMAX; i++)
    {
        if(!bl[i].isFire)continue;
        // 1�ʿ� 200 ����
        bl[i].Speed += DeltaTime * 100.0f;

        bl[i].Pos += bl[i].Dir * DeltaTime * bl[i].Speed;
        //1�ʿ� 180��ȸ��
        //bl[i].Rot += DeltaTime *PI;
    }
    //cout << g_Mouse.x << ","<< g_Mouse.y <<endl;
    child->Rotation +=0.1f;
    //lnChild->Rotation2 += 0.1f;
}

void Scene1::LateUpdate()
{

    rc->WorldUpdate();
    child->WorldUpdate();
    child2->WorldUpdate();
}

void Scene1::Render()
{
    /*child->Render();
    child2->Render();*/
    rc->Render();
    //�߻�� �Ѿ��� �׷��ֱ�
    for(int i = 0; i < BULLETMAX; i++)
    {
        if(!bl[i].isFire) continue;

        //�׷��ֱ�
        ln->Position = bl[i].Pos;
        ln->Rotation = DirToRadian(bl[i].Dir);
        ln->WorldUpdate();
        //ln->Render();

        lnChild->Rotation = -bl[i].Rot;
        lnChild->Rotation2 = bl[i].Rot;
        lnChild->WorldUpdate();
        lnChild->Render();
    }
}
