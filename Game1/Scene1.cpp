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
    Camera::main = cam1;
    loadCount++;


    GM->player = Player::Create();
    loadCount++;


    GM->map = Terrain::Create();
    GM->map->LoadFile("Terrain.xml");
    GM->map->CreateStructuredBuffer();
    loadCount++;
    GM->map->PerlinNoise();//펄린노이즈 적용

    for (int i = 0; i < MONCREATESIZE; ++i)
    {
        int num = i;
      /*  int num = 0;*/
        
        auto newMonster = Monster::Create("Monster", MonsterType(num));
        GM->monsterPool.push_back(newMonster);
    }
    loadCount++;

    astar = new Astar();
    astar->CreateNode(GM->map,50);
    
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
    ImGui::Text("HP : %d", GM->player->Hp);
    for (auto& monster : GM->monsterPool)
    {
        ImGui::Text("MosterState : %d", monster->state);
        ImGui::Text("MosterHp : %d", monster->Hp);
    }

    if (ImGui::Button("Perlin"))
    { 
        GM->map->PerlinNoise();
    }

    if (GM->monsterPool.size()<MAXMONSIZE)
    {
        
        if (monsterCreationTimer >= monsterCreationInterval)
        {
            monsterCreationTimer = 0.0f;
            for (int i = 0; i < MONCREATESIZE; ++i)
            {
               
                int num = RANDOM->Int(0, 2);
               
               
                auto newMonster = Monster::Create("Monster", MonsterType(num));
               
      
                GM->monsterPool.push_back(newMonster);

               
             
            }
          
        }
    }
    
    //downcasting으로 자식에만 있는 함수에 접근하는 방법

    Camera::main->ControlMainCam();
    Camera::main->Update();
    
    
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());


    ImGui::Begin("Hierarchy");
    ////cam1->RenderHierarchy();
    GM->player->PlayerRenderHierarchy();
    ////playerCam->RenderHierarchy();
    for (auto& monster : GM->monsterPool)
    {
        monster->RenderHierarchy();
    }
    GM->map->RenderHierarchy();

   

    ImGui::End();

    /* Golem* temp1 = dynamic_cast<Golem*>(monster);
      if (temp1)
          temp1->Rendertemp();*/
    


    
    
    grid->Update();

    ////playerCam->Update();
    for (auto& monster : GM->monsterPool)
    {
        if (TIMER->GetTick(renewtime, 1.0f))
        {
            astar->PathFinding(monster->GetWorldPos(), GM->player->GetWorldPos(), monster->way);
        }
       monster->Update();
    }
    GM->map->Update();
    GM->Update();//총알
    GM->player->Update();
    

}

void Scene1::LateUpdate()
{
    Ray playerTop;

    playerTop.position = GM->player->GetWorldPos() + Vector3(0, 100, 0);
    playerTop.direction = Vector3(0, -1, 0);

    Vector3 hit;

    if (Utility::RayIntersectMap(playerTop, GM->map, hit))//맵과 몬스터 레이 이용해 플레이어 y값 잡기
    {
        GM->player->SetWorldPosY(hit.y);
    }

    for (auto& monster : GM->monsterPool)
    {
        Ray monTop;
        monTop.position = monster->GetWorldPos() + Vector3(0, 100, 0);
        monTop.direction = Vector3(0, -1, 0);
        if (Utility::RayIntersectMap(monTop, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
        {
            monster->SetWorldPosY(hit.y);
        }
    }
          
           /*Lemurian* temp1 = dynamic_cast<Lemurian*>(monster);
            if (temp1) 
                temp1->CollisionBulletToMap(GM->map);*/
         
        


        //monster->WolrdUpdate();
    //}
    GM->LateUpdate();
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
   GM->map->Render();
   
    for (auto& monster : GM->monsterPool)
    {
        monster->Render();
    }
    GM->Render();
    GM->player->Render();
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


