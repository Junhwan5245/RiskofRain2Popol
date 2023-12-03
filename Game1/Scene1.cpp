#include "stdafx.h"
#include "Scene1.h"

extern int     loadCount;

Scene1::Scene1()
{
    escape = EscapeShip::Create();

    cam1 = Camera::Create();
    cam1->LoadFile("Cam.xml");
    loadCount++;

    teleport = new Teleport();

    skybox = Sky::Create();
    water = Water::Create();

    GM->player = Player::Create();
    loadCount++;

    GM->ui = InGameUI::Create();

    GM->map = Terrain::Create();
    GM->map->LoadFile("Terrain.xml");
    GM->map->CreateStructuredBuffer();
    loadCount++;
    GM->map->PerlinNoise();//�޸������� ����

    GM->map->Update();

    

    for (int i = 0; i < 10; i++)
    {
        Rock1* rock1;
        rock1 = new Rock1();
        GM->featurePool.push_back(rock1);
    }

    for (int i = 0; i < 10; i++)
    {
        itembox[i] = ItemBox::Create();
    }
    
    for (auto& feature : GM->featurePool)
    {
        colliders.emplace_back(feature->feature->Find("RootNode")->collider);
    }

   /* itemBox = ItemBox::Create();*/
    
   for (int i = 0; i < MONCREATESIZE; ++i)
   {
       /*int num = i;*/
       int num = 1;
       
       auto newMonster = Monster::Create("Monster", MonsterType(num));
       GM->monsterPool.push_back(newMonster);
   }
    loadCount++;
    
    boss = Boss::Create("Boss");
   
    int num = 0;
   

    astar = new Astar();

    astar->CreateNode(GM->map,100,colliders);
    
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

    //escape->SetWorldPos(Vector3());
    //escape->anim->ChangeAnimation(AnimationState::ONCE_LAST, 0, 0.1f);
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

    // ī�޶� ����ġ
    if (GM->player->isEscape) //�÷��̾ Ž������ ������
    {
        // �÷��̾��� ��ġ�� Ž������ ����
        GM->player->SetWorldPos(escape->Find("EscapePodMesh")->GetWorldPos());
        // Ž������ �����϶� ī�޶�� Ž������ Root������ Ž������ �ٶ󺸴� ī�޶��
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
        // VŰ�� �������� �۾��� ī�޶�, �÷��̾� ī�޶� ����ġ
        if (INPUT->KeyDown('V'))
            isMainCam = !isMainCam;
        // ī�޶� ��ȯ (�۾��� : cam1 , �÷��̾� : (Camera*)GM->player->Find("PlayerCam") , escapeCam );
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


    if (ImGui::Button("Perlin"))
    { 
        GM->map->PerlinNoise();
    }


    // ���� ���� ��ġ ����
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
    
    //downcasting���� �ڽĿ��� �ִ� �Լ��� �����ϴ� ���




    
    ImGui::Begin("Hierarchy");
    GM->player->PlayerRenderHierarchy();
    for (auto& monster : GM->monsterPool)
    {
        monster->RenderHierarchy();
    }
    for (auto& temp : GM->items)
    {
        temp->item->RenderHierarchy();
    }
    for (auto& feature : GM->featurePool)
    {
        feature->feature->RenderHierarchy();
    }

    GM->ui->RenderH();

    GM->map->RenderHierarchy();
    water->RenderHierarchy();
    
   

    escape->RenderHierarchy();
    ImGui::End();

    /* Golem* temp1 = dynamic_cast<Golem*>(monster);
      if (temp1)
          temp1->Rendertemp();*/
    


    Camera::main->Update();
    teleport->Update();
    itemBox->Update();

    for (int i = 0; i < 10; i++)
    {
        itembox[i]->Update();
    }

    for (auto& monster : GM->monsterPool)
    {
        if (GM->player->isEscape)
        {
            monster->way.clear();
        }
        else
        {
            if (TIMER->GetTick(renewtime, 1.0f))
            {
                astar->PathFinding(monster->GetWorldPos(), GM->player->GetWorldPos(), monster->way);
            }
        }

       monster->Update();
    }
    GM->map->Update();
    for (auto& item : GM->items)
    {
        item->Update();
    }
    for (auto& feature : GM->featurePool)
    {
        feature->Update();
    }
    for (auto& particle : GM->particlePool)
    {
        if (!particle->isPlaying)
        {
            particle->Play();
        }
        particle->Update();
    }

    water->Update();
   
    GM->Update();//�Ѿ�
    GM->player->Update();

    escape->Update();
    GM->ui->Update();
}

void Scene1::LateUpdate()
{
    Ray playerTop;

    playerTop.position = GM->player->GetWorldPos() + Vector3(0, 100, 0);
    playerTop.direction = Vector3(0, -1, 0);

    

    Vector3 hit;
    if (Utility::RayIntersectMap(playerTop, GM->map, hit))//�ʰ� ���� ���� �̿��� �÷��̾� y�� ���
    {
        // float lenght = GM->player->GetWorldPos().y - hit.y;
        // if (lenght < 3 and lenght > 0.2f)
        // {
        //     if (not GM->player->isJumpFinish)
        //     {
        //         GM->player->anim->ChangeAnimation(AnimationState::ONCE_LAST, 16, 0.1f);
        //         GM->player->isJumpFinish = true;
        //     }
        // }

        //GM->player->SetWorldPosY(hit.y);
        if (hit.y > GM->player->GetWorldPos().y)
        {
            GM->player->SetWorldPosY(hit.y + 0.001);
            GM->player->gravity = 0.0f;
            GM->player->isJumpFinish = false;
            GM->player->isJump = false;
        }
    }

    //else
    //{
    //    Vector3 hit2;
    //    Ray playerJumpRay;
    //    playerTop.position = GM->player->GetWorldPos() + Vector3(0, 2, 0);
    //    playerTop.direction = Vector3(0, -1, 0);
    //
    //    if (Utility::RayIntersectTri(playerJumpRay, GM->map, hit2))
    //    {
    //        if (GM->player->GetWorldPos().y < hit.y)
    //        {
    //            GM->player->SetWorldPosY(hit.y);
    //            GM->player->gravity = 0.0f;
    //        }
    //    }
    //    else
    //    {
    //        //�� ������ ��������
    //        GM->player->gravity = 0.0f;
    //    }
    //}



    for (auto& monster : GM->monsterPool)
    {
        Ray monTop;
        monTop.position = monster->GetWorldPos() + Vector3(0, 1000, 0);
        monTop.direction = Vector3(0, -1, 0);
        if (Utility::RayIntersectMap(monTop, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
        {
            monster->SetWorldPosY(hit.y);
        }
    }

    for (auto& feature : GM->featurePool)
    {
        Ray featureTop;
        featureTop.position = feature->feature->GetWorldPos() + Vector3(0, 1000, 0);
        featureTop.direction = Vector3(0, -1, 0);
        if (Utility::RayIntersectMap(featureTop, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
        {
            feature->feature->SetWorldPosY(hit.y);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        Vector3 hit;
        Ray boxTop;
        boxTop.position = itembox[i]->itemBox->GetWorldPos() + Vector3(0, 1000, 0);
        boxTop.direction = Vector3(0, -1, 0);
        if (Utility::RayIntersectMap(boxTop, GM->map, hit))//�ʰ� ���� ���� �̿��� ���� y�� ���
        {
            itembox[i]->itemBox->SetWorldPosY(hit.y);
        }
    }


    
    // �����۰� �÷��̾��� �浹�� �Ͼ�鼭 EŰ�� ��������
    for (auto& i : GM->items)
    {
        if (GM->player->Find("RootNode")->Intersect(i->item->Find("Collider")))
        {
            if (INPUT->KeyDown('E'))
            {
                // ���ڿ��� ���� �������� player Inventory�� �߰�
                GM->player->GetItemInven()->AddItem(i->item->name);

                // �������� �ɷ�
                i->Operate();


                // player Inventory�� �߰��� �������� ����
                cout << "������ '" << i->item->name << "'�� �����˴ϴ�." << endl;
                // �ѹ��� �ϳ��� ���ڸ� ���ٴ� �����Ͽ� items�� ��ü clear
                // ���࿡ �������� ���ٰ� �ϸ�, remove if�� ����
                GM->items.clear();
            }
        }
    }
    


    /* dynamic_cast ���
    Lemurian* temp1 = dynamic_cast<Lemurian*>(monster);
     if (temp1) 
         temp1->CollisionBulletToMap(GM->map);*/
    GM->LateUpdate();

    if (teleport->teleport->Find("RootNode")->Intersect(GM->player->Find("RootNode")))
    {
        if (INPUT->KeyDown('E'))
        { 
            GM->monsterPool.push_back(boss);
            //������ ä��� �� ����
        }
    }
}

void Scene1::PreRender()
{
   
} 

void Scene1::Render()
{
    LIGHT->Set();
    Camera::main->Set();
    skybox->Render();
    //playerCam->Set();
    
    GM->map->Render();
    water->Render();
   
  /*  itemBox->Render();*/
    
    for (int i = 0; i < 10; i++)
    {
        itembox[i]->Render();
    }
    for (auto& item : GM->items)
    {
       item->Render();
    }
    for (auto& monster : GM->monsterPool)
    {
        monster->Render();
    }
    
    for (auto& feature : GM->featurePool)
    {
        feature->Render();
    }
    GM->player->Render();
    GM->Render();
    for (auto& particle : GM->particlePool)
    {
        particle->Render();
    }
    escape->Render();
    teleport->Render();
    GM->ui->Render();
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


