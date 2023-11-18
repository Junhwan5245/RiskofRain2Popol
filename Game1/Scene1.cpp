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
    map->CreateStructuredBuffer();
    //map->PerlinNoise();//펄린노이즈 적용

    for (int i = 0; i < MONCREATESIZE; ++i)
    {
        int num = RANDOM->Int(0, 1);
        auto newMonster = Monster::Create("Monster", MonsterType(num));
        GM->monsterPool.push_back(newMonster);
    }

    astar = new Astar();
    astar->CreateNode(map, 200);
    
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

    for (auto& monster : GM->monsterPool)
    {
        ImGui::Text("MosterState : %d", monster->state);
    }

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
        if (Utility::RayIntersectMap(monTop, map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
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
