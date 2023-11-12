#pragma once

enum class BulletType
{
    PLAYER,
    MONSTER,//나중에 세부적으로 나누면 될듯
};

class Bullet : public Actor
{
public:
	static Bullet* Create(string name = "Bullet");

private:
    BulletType  bulletType;
    
    Vector3     fireDir;      // 쏘는 방향
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

