#pragma once
class PlayerSelectScene : public Scene
{
private:
    Camera* cam1;

    //Actor*  select_player;  //선택된 캐릭터 액터
    UI* bg;

    UI* gameStartButton;        // 시작
    UI* backButton;             // 뒤로가기

    UI* playerSelectBox;        // 좌측 큰 창
    UI* playerSelect[16];       // 캐릭터 선택칸 + 16

    UI* playerExplainButton;    // 개요 버튼
    UI* playerExplain;          // 개요
    // 1개 추가 (글씨만 적혀있는거)

    UI* playerSkillButton;      // 스킬
    UI* playerSkill[4];         // 스킬 0 : LButton, 1 : RButton, 2 : LShift, 3 : R

    UI* playerSKillChange;      // 장전
    // 19개의 UI박스 추가 (스킬 변경)

    UI* optionSelectBox;        // 우측 큰 창
    UI* option_Level;           // 난이도 글씨 박스
    UI* option_LevelSelect[3];  // 난이도 선택 박스
    // 마우스 가져갈때마다 UI하나씩 추가 (총 3개 더 추가)


    UI* option_Expansion;       // 확장팩 글씨 박스
    UI* option_ExpansionSelect; // 아래 잠금 박스 + 1
    UI* option_Relic;           // 유물 글씨 박스
    UI* option_RelicSelect;     // 유물 선택 박스



    UI* ui;

public:
    ~PlayerSelectScene();
    PlayerSelectScene();


    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};