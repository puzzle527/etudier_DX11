#include "stdafx.h"
#include "Player.h"
#include "TileMap/TileMap.h"

Player::Player()
{
    state = PL_IDLE;
    body = new Rect(Vector2(0.0f, 0.0f), false);
    body->Init();
    body->Scale = Vector2(64.0f, 64.0f);
    body->Position = Vector2(400.0f, 300.0f);


    walk = new Image(_T("Walk.png"));
    walk->Init();
    walk->Scale = Vector2(64.0f, 64.0f);
    walk->MaxFrame.x = 6;
    walk->MaxFrame.y = 8;
    walk->ChangeAnim(_STOP, 0.1f);
    walk->P = &body->RT;

    roll = new Image(_T("Roll.png"));
    roll->Init();
    roll->Scale = Vector2(64.0f, 64.0f);
    roll->MaxFrame.x = 6;
    roll->MaxFrame.y = 8;
    roll->ChangeAnim(_STOP, 0.1f);
    roll->P = &body->RT;
    roll->isActive = false;
}

Player::~Player()
{
    delete roll;
    delete walk;
    delete body;
}

HRESULT Player::Init()
{
    return S_OK;
}

void Player::Release()
{
}

void Player::Update()
{
    //길찾기용 움직임
    if (!way.empty())
    {
        from = body->Position;
        body->Position = Lerp(from, to, g);
        //body->Position.y += 10.0f;
        g += DeltaTime * 3.0f;
        if (g > 1.0f)
        {
            g = 0.0f;
            from = way.back()->img->Position;
            from.y += 40.0f;
            way.pop_back();
            if(!way.empty())
            to = way.back()->img->Position;
            to.y += 40.0f;
        }

    }




    if (state == PL_IDLE)
    {
        LookDir = g_Mouse - body->Position;
        SetLook(LookDir, walk);
        //idle->walk
        if (KEYMANAGER->KeyPress('W') ||
            KEYMANAGER->KeyPress('A') ||
            KEYMANAGER->KeyPress('S') ||
            KEYMANAGER->KeyPress('D'))
        {
            walk->ChangeAnim(_LOOP, 0.1f);
            state = PL_WALK;
        }
    }
    else if (state == PL_WALK)
    {
        LookDir = g_Mouse - body->Position;

        SetLook(LookDir,walk);

        //walk->roll
        if (KEYMANAGER->KeyDown(VK_SPACE))
        {
            state = PL_ROLL;
            RollTime = 0.0f;
            walk->isActive = false;
            roll->isActive = true;
            roll->ChangeAnim(_ONCE, 0.1f);
        }

        InputDir = Vector2(0.0f, 0.0f);
        if (KEYMANAGER->KeyPress('W'))
        {
            InputDir.y = 1.0f;
        }
        else if (KEYMANAGER->KeyPress('S'))
        {
            InputDir.y = -1.0f;
        }
        if (KEYMANAGER->KeyPress('A'))
        {
            InputDir.x = -1.0f;
        }
        else if (KEYMANAGER->KeyPress('D'))
        {
            InputDir.x = 1.0f;
        }
        D3DXVec2Normalize(&InputDir, &InputDir);
        Move();
       

        //walk->idle
        if (InputDir == Vector2(0.0f, 0.0f))
        {
            walk->ChangeAnim(_STOP, 0.1f);
            walk->Frame.x = 0;
            state = PL_IDLE;
        }

    }
    else if (state == PL_ROLL)
    {
        // 0 ~ 0.6
        // 0 ~ 90              
        RollTime += DeltaTime * 90.0f / 0.6f * TORADIAN;
        
        SetLook(InputDir, roll);
        Move();
       

        //roll->idle
        if (roll->GetAnimState() == _STOP)
        {
            walk->ChangeAnim(_STOP, 0.1f);
            walk->Frame.x = 0;
            state = PL_IDLE;
            walk->isActive = true;
            roll->isActive = false;
        }
    }

    Foot = body->Position + Vector2(0.0f, -20.0f)
        + InputDir * 10.0f;

    body->WorldUpdate();
    walk->WorldUpdate();
    roll->WorldUpdate();
}

void Player::LateUpdate()
{


    body->WorldUpdate();
    walk->WorldUpdate();
    roll->WorldUpdate();
}

void Player::Render()
{


    body->Render();
    walk->Render();
    roll->Render();
}
void Player::Move(bool dir)
{
    if (dir)
    {
        if (state == PL_WALK)
        {
            body->Position += InputDir
                * 200.0f * DeltaTime;
        }
        if (state == PL_ROLL)
        {
            body->Position += InputDir
                * cosf(RollTime) * 600.0f * DeltaTime;
        }
    }
    else
    {
        if (state == PL_WALK)
        {
            body->Position -= InputDir
                * 200.0f * DeltaTime;
        }
        if (state == PL_ROLL)
        {
            body->Position -= InputDir
                * cosf(RollTime) * 600.0f * DeltaTime;
        }
    }
    
}
void Player::Move2()
{
    /*if (InputDir.y > 0.0f)
    {
        InputDir.y = 0.0f;
    }*/
    /*if (state == PL_WALK)
    {
        body->Position += InputDir
            * 200.0f * DeltaTime;
    }
    if (state == PL_ROLL)
    {
        body->Position += InputDir
            * cosf(RollTime) * 600.0f * DeltaTime;
    }*/
}
void Player::SetLook(Vector2 Dir, Image* target)
{
   
    float Seta = DirToRadian(Dir);
    float Radian225 = PI / 8.0f;
    float Radian45 = PI / 4.0f;

    //RU
    if (Radian225 < Seta and
        Seta <= Radian225 + Radian45)
    {
        target->Frame.y = PL_IMG_RU;
    }
    //U
    else if (Radian225 + Radian45 < Seta and
        Seta <= Radian225 + Radian45 *2.0f)
    {
        target->Frame.y = PL_IMG_U;
    }
    else if (Radian225 + Radian45 * 2.0f < Seta and
        Seta <= Radian225 + Radian45 * 3.0f)
    {
        target->Frame.y = PL_IMG_LU;
    }
    else if (Radian225 + Radian45 * 3.0f < Seta and
        Seta <= Radian225 + Radian45 * 4.0f)
    {
        target->Frame.y = PL_IMG_L;
    }
    else if (Radian225 + Radian45 * 4.0f < Seta and
        Seta <= Radian225 + Radian45 * 5.0f)
    {
        target->Frame.y = PL_IMG_LD;
    }
    else if (Radian225 + Radian45 * 5.0f < Seta and
        Seta <= Radian225 + Radian45 * 6.0f)
    {
        target->Frame.y = PL_IMG_D;
    }
    else if (Radian225 + Radian45 * 6.0f < Seta and
        Seta <= Radian225 + Radian45 * 7.0f)
    {
        target->Frame.y = PL_IMG_RD;
    }
    else
    {
        target->Frame.y = PL_IMG_R;
    }
}
