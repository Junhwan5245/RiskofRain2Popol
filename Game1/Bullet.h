#pragma once

enum class BulletType
{
    PLAYER,
    MONSTER,//���߿� ���������� ������ �ɵ�
};

class Bullet : public Actor
{
public:
	static Bullet* Create(string name = "Bullet");
    Bullet();
    virtual ~Bullet();
    BulletType  bulletType;
      // ��� ����
    Vector3     fireDir;
    float       power;
    bool        isFire;
    bool        isCollsion;
    Ray         BulletRay;
    float       extinctionTime;
    Pop*        bulletParticle;

    virtual Pop*    InitParticle();
    void	Update();
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    CollisionWithMap();
    virtual void    SetPos(Vector3 pos);
    virtual void    Fire(Vector3 dir, float power, Vector3 rotation);

    //bool    GetIsFire() { return isFire; }
};

