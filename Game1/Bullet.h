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
    


protected:
    Bullet();
    virtual ~Bullet();
    BulletType  bulletType;

    Vector3     fireDir;      // ��� ����
    float       power;


public:
    bool        isFire;


    virtual void	Update();
    virtual void	Render(shared_ptr<Shader> pShader = nullptr);

    virtual void    SetPos(Vector3 pos);
    virtual void    Fire(Vector3 dir, float power, Vector3 rotation);

    //bool    GetIsFire() { return isFire; }
};

