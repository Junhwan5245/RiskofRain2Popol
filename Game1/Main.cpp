#include "stdafx.h"
#include "Main.h"
#include "Scene1.h"
#include "LoadingScene.h"
#include "StartScene.h"
#include "PlayerSelectScene.h"


Main::Main()
{

  

}

Main::~Main()
{

}

void Main::Init()
{
    // 로딩신 -> 스타트신 -> 캐릭선택신 -> 게임플레이신
    
    // LOADING SCENE
    SCENE->AddScene("LOADING", new LoadingScene);
    SCENE->ChangeScene("LOADING");

    // START SCENE
    //SCENE->AddScene("StartScene", new StartScene);
    //SCENE->ChangeScene("StartScene"); 

    // SELECT SCENE
    //SCENE->AddScene("PLAYERSELECT", new PlayerSelectScene);
    //SCENE->ChangeScene("PLAYERSELECT");
    
    // 게임플레이신
    //SCENE->AddScene("SC1", new Scene1);
    //SCENE->ChangeScene("SC1"); 

    
}

void Main::Release()
{
   
}

void Main::Update()
{
    SCENE->Update();
  
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
    
}
void Main::PreRender()
{
    SCENE->PreRender();
}

void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{

    SCENE->ResizeScreen();
   
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
    App.SetAppName(L"Game1");
    App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
    Main* main = new Main();
    main->Init();

    int wParam = (int)WIN->Run(main);


    main->Release();
    SafeDelete(main);
    D3D->DeleteSingleton();
    WIN->DeleteSingleton();

    return wParam;
}