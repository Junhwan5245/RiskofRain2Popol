#include "stdafx.h"
#include "PlayerSelectScene.h"

extern int     loadCount;

PlayerSelectScene::PlayerSelectScene()
{
    cam1 = Camera::Create();
    cam1->LoadFile("SelectScene_Cam.xml");
    
    bg = UI::Create();
    bg->LoadFile("UI_StartScene_BackGround.xml");

    gameStartButton = UI::Create();
    gameStartButton->LoadFile("UI_SelectScene_GameStart.xml");
    backButton = UI::Create();
    backButton->LoadFile("UI_SelectScene_Back.xml");

    playerSelectBox = UI::Create();
    playerSelectBox->LoadFile("UI_SelectScene_playerSelectBox.xml");

    playerSelect[0] = UI::Create();
    playerSelect[0]->LoadFile("UI_SelectScene_Image_CommandoIcon.xml");


    optionSelectBox = UI::Create();
    optionSelectBox->LoadFile("UI_SelectScene_optionBox.xml");

    playerExplainButton = UI::Create();
    playerExplainButton->LoadFile("UI_SelectScene_ExplainButton.xml");
    playerExplain = UI::Create();
    playerExplain->LoadFile("UI_SelectScene_Font.xml");
    


    playerSkillButton = UI::Create();
    playerSkillButton->LoadFile("UI_SelectScene_SkillButton.xml");
    for (int i = 0; i < 4; i++)
    {
        playerSkill[i] = UI::Create();
    }
    playerSkill[0]->LoadFile("UI_SelectScene_Font_SkillExplain_LButton.xml");
    playerSkill[1]->LoadFile("UI_SelectScene_Font_SkillExplain_RButton.xml");
    playerSkill[2]->LoadFile("UI_SelectScene_Font_SkillExplain_LShift.xml");
    playerSkill[3]->LoadFile("UI_SelectScene_Font_SkillExplain_R.xml");

    playerSKillChangeButton = UI::Create();
    playerSKillChangeButton->LoadFile("UI_SelectScene_SkillChangeButton.xml");

    option_Level            = UI::Create();
    option_Level->LoadFile("UI_SelectScene_Font_Level.xml");

    option_LevelSelect[0]   = UI::Create();
    option_LevelSelect[0]->LoadFile("UI_SelectScene_Image_Level_Easy.xml");
    option_LevelSelect[1]   = UI::Create();
    option_LevelSelect[1]->LoadFile("UI_SelectScene_Image_Level_Normal.xml");
    option_LevelSelect[2]   = UI::Create();
    option_LevelSelect[2]->LoadFile("UI_SelectScene_Image_Level_Hard.xml");

    player_select = Actor::Create();
    player_select->LoadFile("SelectScene_PlayerSelect.xml");
    player_select->visible = false;


    playerRoll = UI::Create();
    playerRoll->LoadFile("UI_SelectScene_Image_PlayerRoll.xml");
    playerRoll->visible = false;

    loadCount++;
}

PlayerSelectScene::~PlayerSelectScene()
{
}

void PlayerSelectScene::Init()
{
    Camera::main = cam1;

    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();

    playerExplain->visible = false;
    playerSkill[0]->visible = false;
    playerSkill[1]->visible = false;
    playerSkill[2]->visible = false;
    playerSkill[3]->visible = false;

    selectType = SelectType::Explain;

    //level = 1;

    UIClick();

}

void PlayerSelectScene::Release()
{
}

void PlayerSelectScene::Update()
{
    
    Vector3 ndcMouse = Utility::MouseToNDC(Camera::main);
    ImGui::Text("gameStartButton x : %.2f, y : %.2f, z : %.2f", gameStartButton->GetWorldPos().x,
        gameStartButton->GetWorldPos().y, gameStartButton->GetWorldPos().z);
    ImGui::Text("mouseNdc x : %.2f, y : %.2f, z : %.2f", ndcMouse.x,
        ndcMouse.y, ndcMouse.z);

    float left = playerRoll->GetWorldPos().x - playerRoll->S._11;
    float right = playerRoll->GetWorldPos().x + playerRoll->S._11;
    float top = playerRoll->GetWorldPos().y + playerRoll->S._22;
    float bottom = playerRoll->GetWorldPos().y - playerRoll->S._22;
    if (left < ndcMouse.x and ndcMouse.x < right
        and bottom < ndcMouse.y and ndcMouse.y < top)
    {
        if (INPUT->KeyPress(VK_LBUTTON))
        {
            Vector3 Rot;
            Rot.y = INPUT->movePosition.x * 0.025f;
            player_select->rotation.y += -Rot.y;
        }
    }



    if (player_select->anim->currentAnimator.animIdx == 1)
    {
        if (player_select->anim->GetPlayTime() >= 0.99f)
            player_select->anim->ChangeAnimation(AnimationState::LOOP, 0, 0.1f);
    }


    //ImGui::Begin("Hierarchy");
    //player_select->RenderHierarchy();
    //bg->RenderHierarchy();
    //playerSelectBox->RenderHierarchy();
    //playerSelect[0]->RenderHierarchy();
    //optionSelectBox->RenderHierarchy();
    //playerExplainButton->RenderHierarchy();
    //playerExplain->RenderHierarchy();
    //gameStartButton->RenderHierarchy();
    //backButton->RenderHierarchy();
    //playerSkillButton->RenderHierarchy();
    //for (int i = 0; i < 4; i++)
    //{
    //    playerSkill[i]->RenderHierarchy();
    //}
    //option_Level           ->RenderHierarchy();
    //option_LevelSelect[0]  ->RenderHierarchy();
    //option_LevelSelect[1]  ->RenderHierarchy();
    //option_LevelSelect[2]  ->RenderHierarchy();
    //
    //playerSKillChangeButton->RenderHierarchy();
    //ImGui::End();

    if (playerSelectNum == 1)
    {
        if (selectType == SelectType::Explain)
        {
            playerExplain->visible = true;
            for (int i = 0; i < 4; i++)
            {
                playerSkill[i]->visible = false;
            }

            playerExplain->Update();
        }
        if (selectType == SelectType::Skill)
        {
            playerExplain->visible = false;
            for (int i = 0; i < 4; i++)
            {
                playerSkill[i]->visible = true;
                playerSkill[i]->Update();
            }
        }
        if (selectType == SelectType::SkillChange)
        {
            playerExplain->visible = false;
            for (int i = 0; i < 4; i++)
            {
                playerSkill[i]->visible = false;
            }
        }
    }
    

    switch (level)
    {
    case 1:
        Level_select = L"Easy";
        break;
    case 2:
        Level_select = L"Normal";
        break;
    case 3:
        Level_select = L"Hard";
        break;
    default:
        break;
    }


    Camera::main->Update();
    player_select->Update();
    bg->Update();
    playerRoll->Update();
    playerSelectBox->Update();
    playerSelect[0]->Update();
    optionSelectBox->Update();
    gameStartButton->Update();
    backButton->Update();
    playerExplainButton->Update();
    playerSkillButton->Update();
    playerSKillChangeButton->Update();
    option_Level->Update();
    option_LevelSelect[0]->Update();
    option_LevelSelect[1]->Update();
    option_LevelSelect[2]->Update();
}

void PlayerSelectScene::LateUpdate()
{
}

void PlayerSelectScene::PreRender()
{
}

void PlayerSelectScene::Render()
{
    RenderFont();

    cam1->Set();
    LIGHT->Set();
    bg->Render();
    player_select->Render();
    playerRoll->Render();
    playerSelectBox->Render();
    playerSelect[0]->Render();
    optionSelectBox->Render();
    playerExplainButton->Render();
    playerSkillButton->Render();
    playerSKillChangeButton->Render();


    switch (selectType)
    {
    case SelectType::Explain:
        playerExplain->Render();
        break;
    case SelectType::Skill:
        for (int i = 0; i < 4; i++)
        {
            playerSkill[i]->Render();
        }
        break;
    case SelectType::SkillChange:
        break;
    default:
        break;
    }

    gameStartButton->Render();
    backButton->Render();
    
    option_Level->Render();
    option_LevelSelect[0]->Render();
    option_LevelSelect[1]->Render();
    option_LevelSelect[2]->Render();
}

void PlayerSelectScene::ResizeScreen()
{
    cam1->viewport.x = 0.0f;
    cam1->viewport.y = 0.0f;
    cam1->viewport.width = App.GetWidth();
    cam1->viewport.height = App.GetHeight();
    cam1->width = App.GetWidth();
    cam1->height = App.GetHeight();
}

void PlayerSelectScene::UIClick()
{
    // 시작버튼 클릭시 게임 시작
    ((UI*)gameStartButton)->mouseDown = [&]
    {
        cout << "시작버튼 클릭" << endl;
        SCENE->ChangeScene("SC1");
    };

    // 뒤로버튼 클릭시 시작화면으로 이동
    ((UI*)backButton)->mouseDown = [&]
    {
        cout << "뒤로가기버튼 클릭" << endl;
        //SCENE->AddScene("SC1", new Scene1);
        SCENE->ChangeScene("StartScene");
    };

    // 뒤로버튼 클릭시 시작화면으로 이동
    ((UI*)playerSelect[0])->mouseDown = [&]
    {
        player_select->anim->ChangeAnimation(AnimationState::LOOP, 1, 0.1f);
        character_select = L"Commando";
        playerSelectNum = 1;
        player_select->visible = true;
    };



    // 개요UI 클릭시 캐릭터 설명창 on
    ((UI*)playerExplainButton)->mouseDown = [&]
    {
        selectType = SelectType::Explain;
    };

    // 스킬UI 클릭시 캐릭터 스킬창 on
    ((UI*)playerSkillButton)->mouseDown = [&]
    {
        selectType = SelectType::Skill;
    };

    // 장전UI 클릭시 캐릭터 스킬변경창 on
    ((UI*)playerSKillChangeButton)->mouseDown = [&]
    {
        selectType = SelectType::SkillChange;
    };

    // 쉬움 난이도 선택
    ((UI*)option_LevelSelect[0])->mouseDown = [&]
    {
        level = 1;
    };

    // 보통 난이도 선택
    ((UI*)option_LevelSelect[1])->mouseDown = [&]
    {
        level = 2;
    };

    // 어려움 난이도 선택
    ((UI*)option_LevelSelect[2])->mouseDown = [&]
    {
        level = 3;
    };
}

void PlayerSelectScene::RenderFont()
{
    Level = L"난이도 : ";
    character = L"캐릭터 : ";


    RECT rect;
    rect.left = (gameStartButton->GetWorldPos().x + 1) * App.GetHalfWidth() - gameStartButton->scale.y * App.GetHalfWidth() * 2;
    rect.top = (1 - gameStartButton->GetWorldPos().y) * App.GetHalfHeight() - gameStartButton->scale.x * App.GetHalfWidth() * 2;
    rect.right = App.GetWidth();
    rect.bottom = App.GetHeight();
    DWRITE->RenderText(Level, rect, 20, L"바탕체", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

    rect.left = (gameStartButton->GetWorldPos().x + 1) * App.GetHalfWidth();
    rect.top = (1 - gameStartButton->GetWorldPos().y) * App.GetHalfHeight() - gameStartButton->scale.x * App.GetHalfWidth() * 2;
    rect.right = App.GetWidth();
    rect.bottom = App.GetHeight();
    DWRITE->RenderText(Level_select, rect, 20, L"바탕체", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);


    rect.left = (gameStartButton->GetWorldPos().x + 1) * App.GetHalfWidth() - gameStartButton->scale.y * App.GetHalfWidth() * 2;
    rect.top = (1 - gameStartButton->GetWorldPos().y) * App.GetHalfHeight() - gameStartButton->scale.x * App.GetHalfWidth() * 1.5f;
    rect.right = App.GetWidth();
    rect.bottom = App.GetHeight();
    DWRITE->RenderText(character, rect, 20, L"바탕체", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);

    rect.left = (gameStartButton->GetWorldPos().x + 1) * App.GetHalfWidth();
    rect.top = (1 - gameStartButton->GetWorldPos().y) * App.GetHalfHeight() - gameStartButton->scale.x * App.GetHalfWidth() * 1.5f;
    rect.right = App.GetWidth();
    rect.bottom = App.GetHeight();
    DWRITE->RenderText(character_select, rect, 20, L"바탕체", Color(1, 1, 1, 1), DWRITE_FONT_WEIGHT_BOLD);
}
