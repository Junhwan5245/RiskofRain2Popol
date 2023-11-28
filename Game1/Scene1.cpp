#include "stdafx.h"
#include "Scene1.h"

extern int     loadCount;

Scene1::Scene1()
{
    escape = EscapeShip::Create();

    item = Actor::Create("Item");
    item->LoadFile("Item_APRound.xml");
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
    GM->map->PerlinNoise();//펄린노이즈 적용

    //for (int i = 0; i < MONCREATESIZE; ++i)
    //{
    //    int num = i;
    //  /*  int num = 0;*/
    //    
    //    auto newMonster = Monster::Create("Monster", MonsterType(num));
    //    GM->monsterPool.push_back(newMonster);
    //}
    loadCount++;

    astar = new Astar();
    astar->CreateNode(GM->map,50);
    
}
Scene1::~Scene1()
{

}

void Scene1::Init()
{
    Camera::main = (Camera*)escape->Find("EscapeCam");

    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = 1280;
    Camera::main->viewport.height = 720;
    
    Camera::main->width = 1280;
    Camera::main->height = 720;

    
    escape->SetPos();
}

void Scene1::Release()
{
}

void Scene1::Update()
{
    monsterCreationTimer += DELTA;

    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();

    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->ControlMainCam();

    
    if (GM->player->isEscape) //플레이어가 탐사정에 있을때
    {
        // 플레이어의 위치를 탐사정에 고정
        GM->player->SetWorldPos(escape->Find("EscapePodMesh")->GetWorldPos());
        // 탐사정에 고정일때 카메라는 탐사정의 Root값에서 탐사정을 바라보는 카메라로
        Vector3 dir = GM->player->GetWorldPos() - escape->Find("EscapeCam")->GetWorldPos();
        dir.Normalize();

        escape->Find("EscapeCam")->rotation.x = -asinf(dir.y);
        Camera::main = (Camera*)escape->Find("EscapeCam");
        if (INPUT->KeyDown('E'))
        {
            GM->player->isEscape = false;
        }
    }
    else
    {
        // V키를 눌렀을때 작업용 카메라, 플레이어 카메라 스위치
        if (INPUT->KeyDown('V'))
            isMainCam = !isMainCam;
        // 카메라 전환 (작업용 : cam1 , 플레이어 : (Camera*)GM->player->Find("PlayerCam") , escapeCam );
        if (isMainCam)
        {
            Camera::main = cam1;
            Camera::main->ControlMainCam();
        }
        else
        {
            Camera::main = (Camera*)GM->player->Find("PlayerCam");
            MouseHold();
        }
    }


    ImGui::Text("TIMER : %.2f", monsterCreationTimer);
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    ImGui::Text("Stagelevel : %d", level);
    ImGui::Text("HP : %d", GM->player->hp);

    for (auto& monster : GM->monsterPool)
    {
        ImGui::Text("MosterState : %d", monster->state);
        ImGui::Text("MosterHp : %d", monster->Hp);
    }

    if (ImGui::Button("Perlin"))
    { 
        GM->map->PerlinNoise();
    }

    //if (GM->monsterPool.size()<MAXMONSIZE)
    //{
    //    if (monsterCreationTimer >= monsterCreationInterval)
    //    {
    //        monsterCreationTimer = 0.0f;
    //        for (int i = 0; i < MONCREATESIZE; ++i)
    //        {
    //            int num = RANDOM->Int(0, 2);
    //            auto newMonster = Monster::Create("Monster", MonsterType(num));
    //            GM->monsterPool.push_back(newMonster);
    //        }
    //    }
    //}
    
    //downcasting으로 자식에만 있는 함수에 접근하는 방법


    
    ImGui::Begin("Hierarchy");
    GM->player->PlayerRenderHierarchy();
    for (auto& monster : GM->monsterPool)
    {
        monster->RenderHierarchy();
    }
    GM->map->RenderHierarchy();
    escape->RenderHierarchy();
    item->RenderHierarchy();
    ImGui::End();

    /* Golem* temp1 = dynamic_cast<Golem*>(monster);
      if (temp1)
          temp1->Rendertemp();*/
    
    Camera::main->Update();

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
    escape->Update();
    item->Update();

    ui->Update();
}

void Scene1::LateUpdate()
{
    Ray playerTop;

    playerTop.position = GM->player->GetWorldPos() + Vector3(0, 100, 0);
    playerTop.direction = Vector3(0, -1, 0);

    Ray playerJumpRay;
    playerTop.position = GM->player->GetWorldPos() + Vector3(0, 1, 0);
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

    //임시
    Ray itemTop;
    itemTop.position = item->GetWorldPos() + Vector3(0, 10, 0);
    itemTop.direction = Vector3(0, -1, 0);
    if (Utility::RayIntersectMap(itemTop, GM->map, hit))//맵과 몬스터 레이 이용해 몬스터 y값 잡기
    {
        item->SetWorldPosY(hit.y);
    }

    if (GM->player->Find("RootNode")->Intersect(item->Find("APRoundPickup.obj")))
    {
        GM->player->GetItemInven()->AddItem("APRound");
    }

    //임시

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

    GM->map->Render();
   
    for (auto& monster : GM->monsterPool)
    {
        monster->Render();
    }
    GM->Render();
    GM->player->Render();
    escape->Render();
    item->Render();
    ui->Render();
}

void Scene1::ResizeScreen()
{
    Camera::main->viewport.x = 0.0f;
    Camera::main->viewport.y = 0.0f;
    Camera::main->viewport.width = 1280;
    Camera::main->viewport.height = 720;


    Camera::main->width = 1280;
    Camera::main->height = 720;
}

void Scene1::MouseHold()
{
    POINT ptMouse;
    ptMouse.x = App.GetHalfWidth();
    ptMouse.y = App.GetHalfHeight();
    Vector3 Rot;
    Rot.x = (INPUT->position.y - ptMouse.y) * 0.003f;
    Rot.y = (INPUT->position.x - ptMouse.x) * 0.003f;
    GM->player->rotation.y += Rot.y;
    GM->player->Find("PlayerCam")->rotation.x += Rot.x;
    ClientToScreen(App.GetHandle(), &ptMouse);
    SetCursorPos(ptMouse.x, ptMouse.y);
}

void Scene1::SetScene(int stagelv)
{
    level = stagelv;
}


