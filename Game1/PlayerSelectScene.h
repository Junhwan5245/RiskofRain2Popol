#pragma once
class PlayerSelectScene : public Scene
{
private:
    Camera* cam1;

    //Actor*  select_player;  //���õ� ĳ���� ����
    UI* bg;

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