#include "stdafx.h"
#include "Scene2.h"

Scene2::Scene2()
{
    //생성후 바뀌지 않을것
    Bg = new Image(_T("bg.png"),
        Vector2(-0.5f, -0.5f));
    Bg->Init();
    Bg->Scale = Vector2(448.0f, 4288.0f);
    Bg->WorldUpdate();
    Bg->ChangeAddress(_WRAP);

    Pl.Body = new Circle(36, Vector2(0.0f, 0.5f), false);
    Pl.Body->Init();
    Pl.Body->Scale = Vector2(30.0f, 30.0f);
    Pl.Body->color = Color(1.0f, 0.0f, 0.0f, 0.5f);

    Pl.Move = new Image(_T("LeftRight.png"), Vector2(0.0f, 0.5f));
    Pl.Move->Init();
    Pl.Move->MaxFrame.x = 7;
    Pl.Move->Position.y += 20.0f;
    Pl.Move->Scale = Vector2(64.0f, 80.0f);
    Pl.Move->P = &Pl.Body->RT;

    Pl.Boost = new Image(_T("Start.png"), Vector2(0.0f, 0.5f));
    Pl.Boost->Init();
    Pl.Boost->MaxFrame.x = 11;
    Pl.Boost->Scale = Vector2(64.0f, 240.0f);
    Pl.Boost->P = &Pl.Body->RT;
    Pl.Boost->Position.y += 20.0f;
    Pl.Boost->ChangeAnim(_LOOP, 0.1f);

    SOUNDMANAGER->AddSound("gun.wav", "GUN");
    SOUNDMANAGER->AddSound("bgm.wav", "BGM");
    LIGHTMANAGER->light.Radius = 0.0f;
}

Scene2::~Scene2()
{
    delete Pl.Boost;
    delete Pl.Move;
    delete Pl.Body;
    delete Bg;
}

HRESULT Scene2::Init()
{
    //씬을 초기화할때 할것
    Pl.Body->Position = Vector2(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

    Pl.Boost->isActive = false;
    Pl.Move->isActive = true;

    SOUNDMANAGER->Play("BGM");
   
    Bg->UV.y = 0.0f;
    Bg->UV.w = 1.0f;

    FadeoutTime = 0.0f;
    isFadeout = false;

    FadeinTime = 0.0f;
    isFadein = true;

    //SOUNDMANAGER->SetVolume("BGM");
    /*LIGHTMANAGER->light.LightColor
        = Color(0.5f, 0.5f,
            0.5f, 0.5f);
    LIGHTMANAGER->light.Radius = 600.0f;*/

    return S_OK;
}

void Scene2::Release()
{
   
}

void Scene2::Update()
{
    if (KEYMANAGER->KeyDown('1'))
    {
        isFadeout = true;
        
    }
    if (isFadeout)
    {
        FadeoutTime += DeltaTime;
        //조명은 어둡게 배경음은 점점 감소로
        BgmScale = 1.0f- FadeoutTime/2.0f;
        SOUNDMANAGER->SetVolume("BGM", BgmScale);

        /*LIGHTMANAGER->light.LightColor
            = Color(BgmScale/2.0f, BgmScale / 2.0f,
                BgmScale / 2.0f, 0.5f);*/

        LIGHTMANAGER->light.Radius
            -= FadeoutTime*DeltaTime * 300.0f;

        if (FadeoutTime > 2.0f)
        {
            SCENEMANAGER->ChangeScene("sc1")
                ->Init();
            Release();
        }
    }
    if (isFadein)
    {
        FadeinTime += DeltaTime;

        BgmScale = FadeinTime / 2.0f;
        SOUNDMANAGER->SetVolume("BGM", BgmScale);

        /*LIGHTMANAGER->light.LightColor
            = Color(BgmScale/2.0f, BgmScale / 2.0f,
                BgmScale / 2.0f, 0.5f);*/

        LIGHTMANAGER->light.Radius
            += FadeinTime * DeltaTime * 300.0f;

        if (FadeinTime > 2.0f)
        {
            isFadein = false;
        }

    }

    if (ImGui::Button("BGMSTOP"))
    {
        SOUNDMANAGER->Stop("BGM");
    }
    if (ImGui::Button("BGMPLAY"))
    {
        SOUNDMANAGER->Play("BGM");
    }
    if (ImGui::Button("BGMPAUSE"))
    {
        SOUNDMANAGER->Pause("BGM");
    }
    if (ImGui::Button("BGMRESUME"))
    {
        SOUNDMANAGER->Resume("BGM");
    }
    if (ImGui::SliderFloat("BGMSCALE",&BgmScale
    ,0.0f,1.0f))
    {
        SOUNDMANAGER->SetVolume("BGM", BgmScale);
    }


   



    //   1초에 4288.0f 이동
    //   1초에 200.0f 이동
    Bg->UV.y -= DeltaTime * 200.0f / Bg->Scale.y;
    Bg->UV.w -= DeltaTime * 200.0f / Bg->Scale.y;

    if (KEYMANAGER->KeyPress(VK_LEFT))
    {
        Pl.Body->Position
            += LEFT * 100.0f * DeltaTime;
        Pl.Handle -= DeltaTime * 2.0f;
    }
    else if (KEYMANAGER->KeyPress(VK_RIGHT))
    {
        Pl.Body->Position
            += RIGHT * 100.0f * DeltaTime;
        Pl.Handle += DeltaTime * 2.0f;
    }
    //핸들을 놨을때
    else
    {
        if (Pl.Handle > DeltaTime * 2.0f)
        {
            Pl.Handle -= DeltaTime * 2.0f;
        }
        else if (Pl.Handle < -DeltaTime * 2.0f)
        {
            Pl.Handle += DeltaTime * 2.0f;
        }
        else
        {
            Pl.Handle = 0.0f;
        }
    }
    Saturate(Pl.Handle, -1.0f, 1.0f);
    //-1 ~ 1 +1 * 3
    //-> 0 ~ 6
    Pl.Move->Frame.x
        = (Pl.Handle + 1.0f) * 3.0f;


    if (KEYMANAGER->KeyPress(VK_UP))
    {
        Pl.Body->Position
            += UP * 100.0f * DeltaTime;
    }
    else if (KEYMANAGER->KeyPress(VK_DOWN))
    {
        Pl.Body->Position
            += DOWN * 100.0f * DeltaTime;
    }
    if (KEYMANAGER->KeyPress(VK_SPACE))
    {
        SOUNDMANAGER->Play("GUN");
    }

    LIGHTMANAGER->light.ScreenPos
        = Pl.Body->Position;
    LIGHTMANAGER->light.ScreenPos.y
        = WINSIZEY - LIGHTMANAGER->light.ScreenPos.y;





    if (KEYMANAGER->KeyDown('1'))
    {
        Pl.Boost->isActive = true;
        Pl.Move->isActive = false;
    }
    if (KEYMANAGER->KeyDown('2'))
    {
        Pl.Boost->isActive = false;
        Pl.Move->isActive = true;
    }


    Pl.Body->WorldUpdate();
    Pl.Move->WorldUpdate();
    Pl.Boost->WorldUpdate();
}

void Scene2::LateUpdate()
{

    Pl.Body->WorldUpdate();
    Pl.Move->WorldUpdate();
    Pl.Boost->WorldUpdate();
}

void Scene2::Render()
{
    Bg->Render();
    Pl.Move->Render();
    Pl.Boost->Render();
    Pl.Body->Render();
}

