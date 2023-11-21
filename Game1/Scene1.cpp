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

    ui = InGameUI::Create();

    GM->map = Terrain::Create();
    GM->map->LoadFile("Terrain.xml");
    GM->map->CreateStructuredBuffer();
    loadCount++;
    //map->PerlinNoise();//펄린노이즈 적용

    for (int i = 0; i < MONCREATESIZE; ++i)
    {
        int num = RANDOM->Int(0, 1);
        auto newMonster = Monster::Create("Monster", MonsterType(num));
        GM->monsterPool.push_back(newMonster);
    }
    loadCount++;

    astar = new Astar();
    astar->CreateNode(GM->map, 200);
    
}
Scene1::~Scene1()
{

}

void Scene1::Init()
{
    Camera::main = cam1;

    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();

    //Camera::main = (Camera*)GM->player->Find("PlayerCam");
}

void Scene1::Release()
{
}

void Scene1::Update()
{
    monsterCreationTimer += DELTA;

    if (INPUT->KeyDown('V'))
        isMainCam = !isMainCam;
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    if (isMainCam)
    {
        Camera::main = cam1;
    }
    else
    {
        Camera::main = (Camera*)GM->player->Find("PlayerCam");
    }

    ImGui::Text("TIMER : %.2f", monsterCreationTimer);
    ImGui::Text("HP : %d", GM->player->Hp);
    for (auto& monster : GM->monsterPool)
    {
        ImGui::Text("MosterState : %d", monster->state);
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
               
                int num = RANDOM->Int(0, 1);
               
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

    
    
    grid->Update();

    ////playerCam->Update();
    for (auto& monster : GM->monsterPool)
    {
       monster->Update();
    }
    GM->map->Update();
    GM->Update();//총알
    GM->player->Update();
    

    //map->Update();

    ui->Update();

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

    //GM->player->WolrdUpdate();

    for (auto& monster : GM->monsterPool)
    {
        Ray monTop;
        monTop.position = monster->GetWorldPos() + Vector3(0, 100, 0);
        monTop.direction = Vector3(0, -1, 0);
        if (Utility::RayIntersectMap(monTop, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
        {
            monster->SetWorldPosY(hit.y);
        }

        if (monster->state == MonsterState::MOVE)//IDLE 상태일때 길찾기 실행
        {
        astar->PathFinding(monster->GetWorldPos(), GM->player->GetWorldPos(), monster->way);
        }

        if (monster->state == MonsterState::ATTACK)
        {
            monster->way.clear();
        }


        if (not monster->way.empty())//monster->way 가 있을때 
        {
            if (TIMER->GetTick(time, 0.1f))
            {
                Vector3 currentPosition = monster->GetWorldPos();

                if (monster->way.size() >= 2)//way back()을 하게되면 way.back()과 몬스터의 getworldpos가 같기 때문에 안움직임 
                {
                    Vector3 targetPosition = monster->way[monster->way.size() - 2];


                    Vector3 direction = targetPosition - currentPosition;
                    direction.Normalize();


                    float speed = 20.0f;
                    monster->MoveWorldPos(direction * speed * DELTA);

                    float distanceThreshold = 0.1f;
                    if ((targetPosition - monster->GetWorldPos()).Length() < distanceThreshold)
                    {
                        monster->way.pop_back();
                    }
                }

                else// 이렇게 처리하는게 맞나?
                {

                }

            }
        }

           
            /*Lemurian* temp1 = dynamic_cast<Lemurian*>(monster);
            if (temp1) 
                temp1->CollisionBulletToMap(GM->map);*/
         
        


        //monster->WolrdUpdate();
    }
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
    ui->Render();
}

void Scene1::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();



    //(Camera*)(GM->player->Find("PlayerCam"))->viewport.x = 0.0f;
    //(Camera*)GM->player->Find("PlayerCam")->viewport.y = 0.0f;
    //(Camera*)GM->player->Find("PlayerCam")->viewport.width = App.GetWidth();
    //(Camera*)GM->player->Find("PlayerCam")->viewport.height = App.GetHeight();
    //(Camera*)GM->player->Find("PlayerCam")->width = App.GetWidth();
    //(Camera*)GM->player->Find("PlayerCam")->height = App.GetHeight();
}


