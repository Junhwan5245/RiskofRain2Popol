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

    wstring w_playerSelect;
    wstring w_option;
    wstring w_exit;
    wstring w_explan;

public:
    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;
};

