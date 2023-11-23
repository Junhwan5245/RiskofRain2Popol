#pragma once

enum class SelectType
{
    Explain,
    Skill,
    SkillChange,
};

class PlayerSelectScene : public Scene
{
private:
    Camera* cam1;
    Actor* player_select;
    UI* playerRoll;
    SelectType  selectType;

    int playerSelectNum = 0;        //  0 : Default 1 : Commando  2: ???  3 : ???      
    

    //Actor*  select_player;  //���õ� ĳ���� ����
    UI* bg;

    UI* gameStartButton;        // ����
    UI* backButton;             // �ڷΰ���

    UI* playerSelectBox;        // ���� ū â
    UI* playerSelect[16];       // ĳ���� ����ĭ + 16

    UI* playerExplainButton;    // ���� ��ư
    UI* playerExplain;          // ����
    // 1�� �߰� (�۾��� �����ִ°�)

    UI* playerSkillButton;      // ��ų
    UI* playerSkill[4];         // ��ų 0 : LButton, 1 : RButton, 2 : LShift, 3 : R

    UI* playerSKillChangeButton;      // ���� 
    // 19���� UI�ڽ� �߰� (��ų ����)

    UI* optionSelectBox;        // ���� ū â
    UI* option_Level;           // ���̵� �۾� �ڽ�
    UI* option_LevelSelect[3];  // ���̵� ���� �ڽ�
    // ���콺 ������������ UI�ϳ��� �߰� (�� 3�� �� �߰�)


    UI* option_Expansion;       // Ȯ���� �۾� �ڽ�
    UI* option_ExpansionSelect; // �Ʒ� ��� �ڽ� + 1
    UI* option_Relic;           // ���� �۾� �ڽ�
    UI* option_RelicSelect;     // ���� ���� �ڽ�



    UI* ui;

    wstring Level;
    wstring Level_select;
    wstring character;
    wstring character_select;


    int     level = 0;  // 0 = Defualt 1 = easy  2 = normal  3 = hard

public:
    ~PlayerSelectScene();
    PlayerSelectScene();


    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;


    void UIClick();
    void RenderFont();
};