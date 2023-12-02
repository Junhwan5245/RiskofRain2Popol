#pragma once
#define MAXMONSIZE 50 //�ִ� ���ͷ�
#define MONCREATESIZE 3 //�ѹ��� �����Ǵ� ���ͷ�

class Scene1 : public Scene
{
private:
    Camera*         cam1;

    class Astar* astar;
    Sky*         skybox;
    Water*       water;
    ItemBox*     itemBox;
    Boss*        boss;
    EscapeShip*  escape;
    Teleport*    teleport;


    list<Collider*> colliders;
  
    float           monsterCreationTimer = 0.0f;                  // ���� �÷��� �ð�
    const float     monsterCreationInterval = 100.0f;        // ���� ���� �ֱ�

   
    bool            isMainCam;     // ����ķ ��ȯŰ (�ӽÿ�)
    float           renewtime = 0.0f;
    int             level; // ���̵�
public:
    Scene1();
    ~Scene1();

    // Scene��(��) ���� ��ӵ�
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

