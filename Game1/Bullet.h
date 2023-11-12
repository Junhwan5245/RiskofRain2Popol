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

private:
    BulletType  bulletType;
    
    Vector3     fireDir;      // ��� ����
    float       power;


    Bullet();
    virtual ~Bullet();
public:
    bool        isFire;


    void    SetPos(Vector3 pos);
    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr) override;

    void    Fire(Vector3 dir, float power);

    //bool    GetIsFire() { return isFire; }
};

