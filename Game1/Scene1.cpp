#include "stdafx.h"
#include "Scene1.h"

Scene1::Scene1()
{
    grid = Grid::Create();
    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");

    Camera::main = cam1;

    GM->player = Player::Create();

    map = Terrain::Create();
    map->LoadFile("Terrain.xml");
    //map->PerlinNoise();//펄린노이즈 적용

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

    if (ImGui::Button("Perlin"))
    {
        map->PerlinNoise();
    }

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
               
                /*if (newMonster->monType == MonsterType::BEETLE)
                {
                   
                    Beetle* temp1 = dynamic_cast<Beetle*>(newMonster);
                    if (temp1)
                    temp1->temp();

                }*/ 
                //downcasting으로 자식에만 있는 함수에 접근하는 방법
            }
          
        }
    }
    
  

    Camera::main->ControlMainCam();
    Camera::main->Update();
    
    
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    //for (auto& monster : GM->monsterPool)
    //{
    //    ImGui::Text("MonsterState: %d",monster->state);
    //}
    ImGui::Begin("Hierarchy");
    //grid->RenderHierarchy();
    //cam1->RenderHierarchy();
    GM->player->PlayerRenderHierarchy();
    for (auto& monster : GM->monsterPool)
    {
        monster->RenderHierarchy();
    }
    map->RenderHierarchy();
    ImGui::End();

    
    
    grid->Update();
    GM->player->Update();
    for (auto& monster : GM->monsterPool)
    {
        monster->Update();
    }
    map->Update();

    

}

void Scene1::LateUpdate()
{
    Ray playerTop;
   
    
    playerTop.position = GM->player->GetWorldPos() + Vector3(0, 100, 0);
    playerTop.direction = Vector3(0, -1, 0);
    
    Vector3 hit;
    
    if (Utility::RayIntersectMap(playerTop, map, hit))
    {
        GM->player->SetWorldPosY(hit.y);
    }
    
    //GM->player->WolrdUpdate();
    
    for (auto& monster : GM->monsterPool)
    {
        Ray monTop;
        monTop.position = monster->GetWorldPos() + Vector3(0, 100, 0);
        monTop.direction = Vector3(0, -1, 0);
        if (Utility::RayIntersectMap(monTop, map, hit))
        {
            monster->SetWorldPosY(hit.y);
        }

        //monster->WolrdUpdate();
    }
    
   
}

void Scene1::PreRender()
{
   
} 

void Scene1::Render()
{
    LIGHT->Set();
    Camera::main->Set();
    grid->Render();
    map->Render();
    GM->player->Render();
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
