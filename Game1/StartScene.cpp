#include "stdafx.h"
#include "StartScene.h"
#include "Scene1.h"

extern int     loadCount;

StartScene::StartScene()
{
    cam1 = Camera::Create();
    

    //ui = Actor::Create();

    bg = UI::Create();
    bg->LoadFile("UI_StartScene_BackGround.xml");

    logo = UI::Create();
    logo->LoadFile("UI_StartScene_Logo.xml");

    playerSelect = UI::Create();
    playerSelect->LoadFile("UI_StartScene_PlayerSelect.xml");

    option = UI::Create();
    option->LoadFile("UI_StartScene_Option.xml");

    exit = UI::Create();
    exit->LoadFile("UI_StartScene_Exit.xml");

    loadCount++;
}

StartScene::~StartScene()
{
}

void StartScene::Init()
{
    Camera::main = cam1;

    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();

    w_playerSelect = L"싱글 플레이어";
    w_option = L"설정";
    w_exit = L"나가기";

    ((UI*)playerSelect)->mouseDown = [&]
    {
        cout << "playerSelect 클릭" << endl;
        //SCENE->AddScene("SC1", new Scene1);
        SCENE->ChangeScene("PlayerSelect");
    };
    ((UI*)option)->mouseDown = [&]
    {
        cout << "option 클릭" << endl;
    };
    ((UI*)exit)->mouseDown = [&]
    {
        cout << "exit 클릭" << endl;
        PostQuitMessage(0);
    };
}

void StartScene::Release()
{
}

void StartScene::Update()
{
    ImGui::Begin("Hierarchy");
    //ui->RenderHierarchy();
    bg->RenderHierarchy();
    logo->RenderHierarchy();
    playerSelect->RenderHierarchy();
    option->RenderHierarchy();
    exit->RenderHierarchy();
    ImGui::End();

    if (INPUT->KeyPress('L'))
    {
        playerSelect->material->diffuseMap->LoadFile("texUICleanPanel.png");
    }



    Camera::main->Update();
    bg->Update();
    logo->Update();
    playerSelect->Update();
    option->Update();
    exit->Update();
    //ui->Update();
}

void StartScene::LateUpdate()
{
    //Ray Up;
    //Up = Utility::MouseToRay();
    ////Up.position = Vector3(0, 1000, 0);
    ////Up.direction = Vector3(0, -1, 0);
    //Vector3 Hit;
    //for (int i = 0; i < 20; i++)
    //{
    //    if (fruit[i]->GetIsFire())
    //    {
    //        if (fruit[i]->Find("Body")->Intersect(Up, Hit))
    //        {
    //            fruit[i]->Boom();
    //        }
    //    }
    //}
}

void StartScene::PreRender()
{
}

void StartScene::Render()
{
    //RECT r_playerSelect;
    //r_playerSelect.left = playerSelect->GetWorldPos().x - playerSelect->scale.x * 0.5f + 20;
    //r_playerSelect.top = playerSelect->GetWorldPos().y - playerSelect->scale.y * 0.5f +5;
    //r_playerSelect.right = playerSelect->scale.x;
    //r_playerSelect.bottom = playerSelect->scale.y;
    
    //Vector3 pos = Vector3::Transform(playerSelect->GetWorldPos(), Matrix::T);

    DWRITE->RenderText(w_playerSelect, r_playerSelect, 18, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);
    DWRITE->RenderText(w_option, RECT{ 110,1000,1000,472 }, 18, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);
    DWRITE->RenderText(w_exit, RECT{ 110,1000,1000,525 }, 18, L"Noto Sans CJK KR Regular", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);


    cam1->Set();
    LIGHT->Set();
    bg->Render();
    logo->Render();
    playerSelect->Render();
    option->Render();
    exit->Render();

    //ui->Render();
}

void StartScene::ResizeScreen()
{
    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();
}
