#pragma once
class PlayerSelectScene : public Scene
{
private:
    Camera* cam1;

    //Actor*  select_player;  //선택된 캐릭터 액터
    UI* bg;

    UI* ui;

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