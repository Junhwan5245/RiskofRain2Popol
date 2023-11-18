#include "stdafx.h"
#include "PlayerSelectScene.h"

extern int     loadCount;

PlayerSelectScene::PlayerSelectScene()
{
    cam1 = Camera::Create();
    
    bg = UI::Create();
    bg->LoadFile("UI_StartScene_BackGround.xml");

    gameStartButton = UI::Create();
    gameStartButton->LoadFile("UI_SelectScene_GameStart.xml");
    backButton = UI::Create();
    backButton->LoadFile("UI_SelectScene_Back.xml");

    playerSelectBox = UI::Create();
    playerSelectBox->LoadFile("UI_SelectScene_playerSelectBox.xml");

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

    ((UI*)gameStartButton)->mouseDown = [&]
    {
        cout << "시작버튼 클릭" << endl;
        //SCENE->AddScene("SC1", new Scene1);
        SCENE->ChangeScene("SC1");
    }; 
    
    ((UI*)backButton)->mouseDown = [&]
    {
        cout << "뒤로가기버튼 클릭" << endl;
        //SCENE->AddScene("SC1", new Scene1);
        SCENE->ChangeScene("StartScene");
    };

    ((UI*)playerExplainButton)->mouseDown = [&]
    {
        selectType = SelectType::Explain;
    };

    ((UI*)playerSkillButton)->mouseDown = [&]
    {
        selectType = SelectType::Skill;
    };

    ((UI*)playerSKillChangeButton)->mouseDown = [&]
    {
        selectType = SelectType::SkillChange;
    };
	//ui = UI::Create();
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


    ImGui::Begin("Hierarchy");
    //ui->RenderHierarchy();
    bg->RenderHierarchy();
    playerSelectBox->RenderHierarchy();
    optionSelectBox->RenderHierarchy();
    playerExplainButton->RenderHierarchy();
    playerExplain->RenderHierarchy();
    gameStartButton->RenderHierarchy();
    backButton->RenderHierarchy();
    playerSkillButton->RenderHierarchy();
    for (int i = 0; i < 4; i++)
    {
        playerSkill[i]->RenderHierarchy();
    }
    playerSKillChangeButton->RenderHierarchy();
    ImGui::End();


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


    Camera::main->Update();
    bg->Update();
    playerSelectBox->Update();
    optionSelectBox->Update();
    gameStartButton->Update();
    backButton->Update();
    playerExplainButton->Update();
    playerSkillButton->Update();
    playerSKillChangeButton->Update();
}

void PlayerSelectScene::LateUpdate()
{
}

void PlayerSelectScene::PreRender()
{
}

void PlayerSelectScene::Render()
{
    cam1->Set();
    LIGHT->Set();
    bg->Render();
    playerSelectBox->Render();
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
