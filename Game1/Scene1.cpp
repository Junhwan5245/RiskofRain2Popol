#include "stdafx.h"
#include "Scene1.h"

//extern wstring loadObejct;
//extern int     loadCount;



Scene1::Scene1()
{
   /* loadObejct = L"Grid";  */
    grid = Grid::Create();
  /*  loadCount++;*/

   /* loadObejct = L"Cam";*/
    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");

    Camera::main = cam1;

   /* int num = RANDOM->Int(0, 1);
    monster = Monster::Create("Monster", MonsterType(num));*/
    /*loadObejct = L"Monster";*/

     

   
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
   
    //player->LoadFile("Vam.xml");
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
    grid->RenderHierarchy();
    cam1->RenderHierarchy();
    for (auto& monster : GM->monsterPool)
    {
        monster->RenderHierarchy();
    }
    ImGui::End();


    grid->Update();
    /*monster->Update();*/
    for (auto& monster : GM->monsterPool)
    {
        monster->Update();
    }
   
   

}

void Scene1::LateUpdate()
{
    //Ray top;
    //top.position = player->GetWorldPos() + Vector3(0, 100, 0);
    //top.direction = Vector3(0, -1, 0);
    //Vector3 hit;
    //if (Utility::RayIntersectMap(top, map, hit))
    //{
    //    player->SetWorldPosY(hit.y);
    //}
    //player->WolrdUpdate();
    //Vector3 dir = player->GetWorldPos() - player->GetLast();
    //Vector3 dir2 = dir;
    //dir2.y = 0;
    //dir.Normalize();
    //dir2.Normalize();
    //float dot = dir.Dot(dir2);
    ////cout << dot << endl;
    //if (player->GetState() == ZamongState::MOVE)
    //{
    //    if (dot < 0.7 and (player->GetWorldPos().y > player->GetLast().y))
    //    {
    //        player->SetWorldPos(player->GetLast());
    //        player->WolrdUpdate();
    //    }
    //}

    //if (INPUT->KeyPress(VK_RBUTTON))
    //{
    //    Ray zamongRay = Utility::MouseToRay();

    //    Vector3 hit;
    //    //광선충돌시에
    //    GameObject* temp = map;
    //    //광선충돌시에
    //    //if (Utility::RayIntersectTri(zamongRay, map, hit))
    //    /*if (map->ComPutePicking(zamongRay,hit))
    //    {
    //        player->SetWorldPos(hit);
    //    }*/
    //}
    //if (INPUT->KeyDown('Q'))
    //{
    //    

    //}
}

void Scene1::PreRender()
{
   
   
   /* map->Render(RESOURCE->shaders.Load("5.Cube_CR.hlsl"));
    player->Render(RESOURCE->shaders.Load("4.Instance_CR.hlsl"));*/
   
   

} 

void Scene1::Render()
{
    Camera::main->Set();
   /* LIGHT->Set();*/
    grid->Render();
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
