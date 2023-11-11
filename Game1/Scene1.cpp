#include "stdafx.h"
#include "Scene1.h"

Scene1::Scene1()
{
    grid = Grid::Create();
    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");

    Camera::main = cam1;
   
    player = Player::Create();

    for (int i = 0; i < MONCREATESIZE; ++i)
    {
        int num = RANDOM->Int(0, 1);
        auto newMonster = Monster::Create("Monster", MonsterType(num));
        GM->monsterPool.push_back(newMonster);
    }
    
}
Scene1::~Scene1()
{

}

void Scene1::Init()
{
}

void Scene1::Release()
{
}

void Scene1::Update()
{
    monsterCreationTimer += DELTA;

    ImGui::Text("TIMER : %.2f", monsterCreationTimer);

    if (GM->monsterPool.size()<MAXMONSIZE)
    {
        if (monsterCreationTimer >= monsterCreationInterval)
        {
            monsterCreationTimer = 0.0f;
            for (int i = 0; i < MONCREATESIZE; ++i)
            {
                int num = RANDOM->Int(0, 1);
                auto newMonster = Monster::Create("Monster", MonsterType(num));

                GM->monsterPool.push_back(newMonster);
            }
          
        }
    }

    Camera::main->ControlMainCam();
    Camera::main->Update();
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Begin("Hierarchy");
    //grid->RenderHierarchy();
    player->RenderHierarchy();
    //cam1->RenderHierarchy();
    for (auto& monster : GM->monsterPool)
    {
        monster->RenderHierarchy();
    }
    ImGui::End();


    grid->Update();
    player->Update();
    /*monster->Update();*/
    for (auto& monster : GM->monsterPool)
    {
        monster->Update();
    }
}

void Scene1::LateUpdate()
{
}

void Scene1::PreRender()
{
} 

void Scene1::Render()
{
    Camera::main->Set();
    grid->Render();
    player->Render();
    for (auto& monster : GM->monsterPool)
    {
        monster->Render();
    }
}

void Scene1::ResizeScreen()
{
    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();

    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();
}
