#include "stdafx.h"
#include "Scene1.h"

//과제 원그리기
//회전이동크기 변환 구현

HRESULT Scene1::Init()
{


    //중심점을 -0.5f만큼 이동
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
    //차일드객체의 부모행렬은 rc의 회전이동행렬
    child->P = &rc->RT;

    child2 = new Rect();
    child2->Init();
    child2->Position = Vector2(70, 70);
    child2->Rotation = 0.0f;
    child2->Scale = Vector2(30, 30);
    child2->isAxis = true;
    //차일2드객체의 부모행렬은 rc의 회전이동행렬
    child2->P = &child->RT;


    //그려줄총알을 30크기로만 설정
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

    // & | ^ 비트연산자
    //이동
    if(KEYMANAGER->KeyPress('W'))
    {

        //등가속-> 가속도가 일정한값

        //초당 100속도 증가
        //속도    가속도
        rcSpeed += DeltaTime * 200.0f;

        //초당 100픽셀만큼 이동
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
    //반시계회전
    //if(KEYMANAGER->KeyPress('A'))
    //{
    //   rc->Rotation -=0.1f;
    //}
    ////시계방향회전
    //if(KEYMANAGER->KeyPress('D'))
    //{
    //    rc->Rotation += 0.1f;
    //}
    if(KEYMANAGER->KeyDown(VK_LBUTTON))
    {
        //한발씩발사
        for(int i = 0; i < BULLETMAX; i++)
        {
            //발사된놈은 거르고 발사안된놈을 찾기
            if(bl[i].isFire)continue;

            //발사됨이라고 만들기
            bl[i].isFire = true;
            bl[i].Pos = rc->Position;
            bl[i].Dir = rc->Right;
            bl[i].Rot = 0.0f;
            //1초당 0움직임
            bl[i].Speed = -200.0f;
            //bl[i].Rot = rc->Rotation;
            break;//한발만쏴야해서 반복문 탈출
        }
    }
    
    //발사된 총알은 날아가게 하기
    for(int i = 0; i < BULLETMAX; i++)
    {
        if(!bl[i].isFire)continue;
        // 1초에 200 증가
        bl[i].Speed += DeltaTime * 100.0f;

        bl[i].Pos += bl[i].Dir * DeltaTime * bl[i].Speed;
        //1초에 180도회전
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
    //발사된 총알은 그려주기
    for(int i = 0; i < BULLETMAX; i++)
    {
        if(!bl[i].isFire) continue;

        //그려주기
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
