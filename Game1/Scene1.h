#pragma once
#define MAXMONSIZE 50 //최대 몬스터량
#define MONCREATESIZE 3 //한번에 생성되는 몬스터량

class Scene1 : public Scene
{
private:
    Camera*         cam1;
    class InGameUI* ui;

    Camera*     playerCam;
    Grid*       grid;
    Monster*    monster;
    
    class Astar* astar;
    Sky*         skybox;
    Water*       water;
    ItemBox*     itemBox;
   
    EscapeShip*     escape;

    Actor* item;        // 임의의 아이템


    float           monsterCreationTimer = 0.0f;                  // 게임 플레이 시간
    const float     monsterCreationInterval = 10.0f;        // 몬스터 생성 주기


    bool            isMainCam;     // 메인캠 전환키 (임시용)
    float           renewtime = 0.0f;
    int             level;
public:
    Scene1();
    ~Scene1();

    // Scene을(를) 통해 상속됨
    virtual void Init() override;
    virtual void Release() override;
    virtual void Update() override;
    virtual void LateUpdate() override;
    virtual void PreRender() override;
    virtual void Render() override;
    virtual void ResizeScreen() override;//
  

    void MouseHold();
    void SetScene(int stagelv);
};

