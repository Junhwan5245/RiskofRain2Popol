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

    UI* idSelect; // 닉네임리스트
    UI* id; // 가운데 창
    UI* newID;    // 우측 위

    wstring w_explan;

    wstring w_id;
    wstring w_idName;

public:
    StartScene();
    ~StartScene();


    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

