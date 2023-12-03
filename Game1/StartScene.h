#pragma once
class StartScene : public Scene
{
private:
    Camera* cam1;
    Actor* ui;

    UI* bg;
    UI* logo;
    UI* playerSelect;
    UI* option;
    UI* exit;

    UI* idSelect; // �г��Ӹ���Ʈ
    UI* id; // ��� â
    UI* newID;    // ���� ��

    wstring w_explan;

    wstring w_id;
    wstring w_idName;

public:
    StartScene();
    ~StartScene();


    // Scene��(��) ���� ��ӵ�
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

