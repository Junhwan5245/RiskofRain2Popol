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
    


protected:
    Bullet();
    virtual ~Bullet();
    BulletType  bulletType;

    Vector3     fireDir;      // 쏘는 방향
    float       power;


public:
    bool        isFire;


    virtual void	Update();
    virtual void	Render(shared_ptr<Shader> pShader = nullptr);

    virtual void    SetPos(Vector3 pos);
    virtual void    Fire(Vector3 dir, float power, Vector3 rotation);

    //bool    GetIsFire() { return isFire; }
};

