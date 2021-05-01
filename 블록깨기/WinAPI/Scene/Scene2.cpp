#include "stdafx.h"
#include "Scene2.h"

HRESULT Scene2::Init()
{
    pl = new Rect();
    pl->Init();
    pl->Position = Vector2(400.0f, 300.0f);
    pl->Scale = Vector2(100.0f, 100.0f);

    cannon = new Line();
    cannon->Init();
    cannon->Position = Vector2(0.0f, 0.0f);
    cannon->Scale = Vector2(130.0f, 100.0f);
    cannon->P = &pl->RT;

    //발사위치
    FirePos = new Object();
    FirePos->Init();
    FirePos->Position = Vector2(130.0f, 0.0f);
    //부모행렬을 캐논으로 둔다
    FirePos->P = &cannon->RT;

    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc = new Circle();
        bl[i].cc->Init();
        bl[i].cc->Scale = Vector2(30.0f, 30.0f);
        bl[i].cc->isActive = false;
        bl[i].cc->isAxis = true;
    }


    return S_OK;
}

void Scene2::Release()
{
    delete cannon;
    delete pl;
    delete FirePos;
    for (int i = 0; i < BALLMAX; i++)
    {
        delete bl[i].cc;
    }

}

void Scene2::Update()
{
    ImGui::ColorEdit4("plColor", pl->color);
    ImGui::SliderFloat("cor", &cor,0.0f,2.0f);

    //캐릭터 이동
    if (KEYMANAGER->KeyPress('W'))
    {
        pl->Position += UP * 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('S'))
    {
        pl->Position += DOWN * 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('A'))
    {
        pl->Position += LEFT * 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress('D'))
    {
        pl->Position += RIGHT * 100.0f * DeltaTime;
    }
    //캐논 돌리기
    cannon->Rotation = DirToRadian(g_Mouse - pl->Position);
   

    //공 발사
    if (KEYMANAGER->KeyDown(VK_LBUTTON))
    {
        for (int i = 0; i < BALLMAX; i++)
        {
            if (!bl[i].cc->isActive)
            {
                bl[i].cc->isActive = true;
                bl[i].gravity = 0.0f;
                bl[i].cc->Position
                    = FirePos->GetWorldPos();
                bl[i].dir
                    = Vector2(cosf(cannon->Rotation),
                        sinf(cannon->Rotation));

                break;
            }
        }
    }

    //발사된총알 속도값 만들기
    for (int i = 0; i < BALLMAX; i++)
    {
        if (bl[i].cc->isActive)
        {
            //속도는             방향 * 크기
            bl[i].velocity = bl[i].dir * bl[i].speed * DeltaTime;
            bl[i].velocity += DOWN * bl[i].gravity * DeltaTime;
            
            //중력은 등가속 운동 (p/s2)
            bl[i].gravity += 150.0f * DeltaTime;
            
            bl[i].cc->Position
                += bl[i].velocity;
        }
    }
  

    pl->WorldUpdate();
    cannon->WorldUpdate();
    FirePos->WorldUpdate();
    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc->WorldUpdate();
    }
}

void Scene2::LateUpdate()
{
    //월드값 갱신후 충돌

   
    for (int i = 0; i < BALLMAX; i++)
    {
        if (!bl[i].cc->isActive) continue;
        //왼쪽, 오른쪽 벽이랑 부딪혔을때
        if (bl[i].cc->Position.x < 15.0f||
            bl[i].cc->Position.x >WINSIZEX - 15.0f)
        {
            bl[i].dir.x *= -1.0f;
            bl[i].speed *= cor;
            //ReverseSeta(bl[i].cc->Rotation, false);
        }
        //위쪽, 아래쪽 벽이랑 부딪혔을때
        if (bl[i].cc->Position.y < 15.0f ||
            bl[i].cc->Position.y >WINSIZEY - 15.0f)
        {
            bl[i].dir.y *= -1.0f;
            //작용 반작용      반발계수
            bl[i].gravity *= -cor;
            bl[i].speed *= cor;

            //ReverseSeta(bl[i].cc->Rotation, true);
        }

        //공끼리 부딪혔을때
        for (int j = i + 1; j < BALLMAX; j++)
        {
            if (ColCir(bl[i].cc, bl[j].cc))
            {
                Vector2 Dir
                    = bl[i].cc->Position - bl[j].cc->Position;
                D3DXVec2Normalize(&Dir, &Dir);
                bl[i].dir = Dir;
                Dir *= -1.0f;
                bl[j].dir = Dir;
                bl[i].speed *= cor;
                bl[j].speed *= cor;
            }
        }


        //벽안으로 좌표를 제한
        Saturate(bl[i].cc->Position.x, 15.0f, WINSIZEX - 15.0f);
        Saturate(bl[i].cc->Position.y, 15.0f, WINSIZEY - 15.0f);

    }
    
    

    //월드값 다시 갱신
    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc->WorldUpdate();
    }
 
}

void Scene2::Render()
{
    pl->Render();
    cannon->Render();
    for (int i = 0; i < BALLMAX; i++)
    {
        bl[i].cc->Render();
    }
}
