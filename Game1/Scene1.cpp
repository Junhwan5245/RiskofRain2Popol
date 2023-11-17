#include "stdafx.h"
#include "Scene1.h"

extern int     loadCount;

Scene1::Scene1()
{
    grid = Grid::Create();
    grid->visible = false;
    loadCount++;

    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");
    
    loadCount++;


    GM->player = Player::Create();
    loadCount++;


    map = Terrain::Create();
    map->LoadFile("Terrain.xml");
    loadCount++;
    //map->PerlinNoise();//펄린노이즈 적용

    for (int i = 0; i < MONCREATESIZE; ++i)
    {
        int num = RANDOM->Int(0, 1);
        auto newMonster = Monster::Create("Monster", MonsterType(num));
        GM->monsterPool.push_back(newMonster);
    }
    loadCount++;
}
Scene1::~Scene1()
{

}

void Scene1::Init()
{
    Camera::main = cam1;
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


    ImGui::Begin("Hierarchy");
    //cam1->RenderHierarchy();
    GM->player->PlayerRenderHierarchy();
    //playerCam->RenderHierarchy();
    //for (auto& monster : GM->monsterPool)
    //{
    //    monster->RenderHierarchy();
    //}
    map->RenderHierarchy();
    ImGui::End();

    
    
    grid->Update();
    GM->player->Update();
    //playerCam->Update();
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
    //playerCam->Set();
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
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
}
