#include "stdafx.h"
#include "Monster.h"
#include "Player.h"


Monster::Monster()
{
    state = MON_IDLE;
    body = new Rect(Vector2(0.0f, 0.0f), false);
    body->Init();
    body->Scale = Vector2(128.0f, 127.0f);
    body->Position = Vector2(800.0f, 600.0f);


    head = new Image(_T("boss.bmp"));
    head->Init();
    head->Scale = Vector2(128.0f, 127.0f);
    head->MaxFrame.y = 8;
    head->ChangeAnim(_STOP, 0.1f);
    head->P = &body->RT;

    DebugRender = new Circle(36,Vector2(0.0f, 0.0f), false);
    DebugRender->Init();
    DebugRender->P = &body->RT;
    DebugRender->color = Color(0, 0, 0, 1);

    pl = nullptr;
    AttTime = 0.0f;
}

Monster::~Monster()
{
    delete DebugRender;
    delete head;
    delete body;

}

HRESULT Monster::Init()
{



    return S_OK;
}

void Monster::Release()
{
}

void Monster::Update()
{
    ImGui::SliderInt("MONSTATE", &state, 0, 3);


    if (state == MON_IDLE)
    {
        
        LookDir = pl->Getbody()->Position - body->Position;
        //idle -> look
        if (Length(&LookDir) < MON_LOOK)
        {
            state = MON_LOOK;
        }
    }
    else if (state == MON_LOOK)
    {
        LookDir = pl->Getbody()->Position - body->Position;
        SetLook(LookDir, head);

        //look -> move
        if (Length(&LookDir) < MON_MOVE)
        {
            state = MON_MOVE;
        }
        //look -> idle
        if (Length(&LookDir) > MON_LOOK)
        {
            state = MON_IDLE;
        }
    }
    else if (state == MON_MOVE)
    {
        LookDir = pl->Getbody()->Position - body->Position;
        SetLook(LookDir, head);

        //move -> att
        if (Length(&LookDir) < MON_ATTACK)
        {
            state = MON_ATTACK;
        }
        //move -> look
        if (Length(&LookDir) > MON_MOVE)
        {
            state = MON_LOOK;
        }


        D3DXVec2Normalize(&LookDir, &LookDir);
        body->Position += LookDir * 150.0f * DeltaTime;
    }
    else if (state == MON_ATTACK)
    {
        LookDir = pl->Getbody()->Position - body->Position;
        //move -> look
        if (Length(&LookDir) > MON_ATTACK)
        {
            state = MON_MOVE;
        }

        AttTime += DeltaTime * 4.0f;
        int D = (int)AttTime ;

        if (D % 2 == 0)//Â¦¼öÃÊÀÏ¶§ °¡·Î·Î ´Ã¸®±â
        {
            //                0~ 1
            head->Scale.x += (AttTime - D) * 100.0f * DeltaTime;
            head->Scale.y -= (AttTime - D) * 100.0f * DeltaTime;
        }
        else//È¦¼ö
        {
            head->Scale.x -= (AttTime - D) * 100.0f * DeltaTime;
            head->Scale.y += (AttTime - D) * 100.0f * DeltaTime;
        }

        /*head->Scale.x += RndFloat(-10.0f, 10.0f);
        head->Scale.y += RndFloat(-10.0f, 10.0f);*/

    }
    DebugRender->WorldUpdate();
    head->WorldUpdate();
    body->WorldUpdate();
}

void Monster::LateUpdate()
{

    DebugRender->WorldUpdate();
    head->WorldUpdate();
    body->WorldUpdate();
}

void Monster::Render()
{
    DebugRender->Scale = Vector2(MON_LOOK * 2.0f, MON_LOOK * 2.0f);
    DebugRender->WorldUpdate();
    DebugRender->Render();
    DebugRender->Scale = Vector2(MON_MOVE * 2.0f, MON_MOVE * 2.0f);
    DebugRender->WorldUpdate();
    DebugRender->Render();
    DebugRender->Scale = Vector2(MON_ATTACK * 2.0f, MON_ATTACK * 2.0f);
    DebugRender->WorldUpdate();
    DebugRender->Render();
    head->Render();
    body->Render();
}

void Monster::SetLook(Vector2 Dir, Image* target)
{

    float Seta = DirToRadian(Dir);
    float Radian225 = PI / 8.0f;
    float Radian45 = PI / 4.0f;

    //RU
    if (Radian225 < Seta and
        Seta <= Radian225 + Radian45)
    {
        target->Frame.y = MON_IMG_RU;
    }
    //U
    else if (Radian225 + Radian45 < Seta and
        Seta <= Radian225 + Radian45 * 2.0f)
    {
        target->Frame.y = MON_IMG_U;
    }
    else if (Radian225 + Radian45 * 2.0f < Seta and
        Seta <= Radian225 + Radian45 * 3.0f)
    {
        target->Frame.y = MON_IMG_LU;
    }
    else if (Radian225 + Radian45 * 3.0f < Seta and
        Seta <= Radian225 + Radian45 * 4.0f)
    {
        target->Frame.y = MON_IMG_L;
    }
    else if (Radian225 + Radian45 * 4.0f < Seta and
        Seta <= Radian225 + Radian45 * 5.0f)
    {
        target->Frame.y = MON_IMG_LD;
    }
    else if (Radian225 + Radian45 * 5.0f < Seta and
        Seta <= Radian225 + Radian45 * 6.0f)
    {
        target->Frame.y = MON_IMG_D;
    }
    else if (Radian225 + Radian45 * 6.0f < Seta and
        Seta <= Radian225 + Radian45 * 7.0f)
    {
        target->Frame.y = MON_IMG_RD;
    }
    else
    {
        target->Frame.y = MON_IMG_R;
    }
}