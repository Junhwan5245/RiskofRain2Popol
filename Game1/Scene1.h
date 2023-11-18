#pragma once
#define MAXMONSIZE 50 //�ִ� ���ͷ�
#define MONCREATESIZE 5 //�ѹ��� �����Ǵ� ���ͷ�

class Scene1 : public Scene
{
private:
    Camera*     cam1;
    Grid*       grid;
    Monster*    monster;
    Terrain*    map;
    float monsterCreationTimer = 0.0f;
    const float monsterCreationInterval = 100.0f;
    class Astar* astar;
    
    float			time = 0;
    
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
};

