#pragma once
class PlayerSelectScene : public Scene
{
private:
    Camera* cam1;

    //Actor*  select_player;  //���õ� ĳ���� ����
    UI* bg;

    UI* gameStartButton;

    UI* playerSelectBox;        // ���� ū â
    UI* playerSelect[16];       // ĳ���� ����ĭ + 16

    UI* playerExplain;          // ����
    // 1�� �߰� (�۾��� �����ִ°�)

    UI* playerSkill;            // ��ų
    // 5�� �߰� (��ų ������)

    UI* playerSKillChange;      // ����
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

public:
    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};