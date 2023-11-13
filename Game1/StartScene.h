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
