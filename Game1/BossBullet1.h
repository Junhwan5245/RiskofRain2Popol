#pragma once
class BossBullet1 : public Bullet
{
public:
    static BossBullet1* Create(string name = "LemurianBullet");
private:
    BossBullet1();

public:
    virtual ~BossBullet1();
    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    Fire(Vector3 dir, float power, Vector3 rotation) override;
    Pop*    InitParticle() override;
};

