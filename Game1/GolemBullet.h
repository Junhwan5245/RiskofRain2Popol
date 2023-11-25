#pragma once
class GolemBullet : public Bullet
{
public:
    static GolemBullet* Create(string name = "GolemBullet");
private:

    GolemBullet();

public:
    virtual ~GolemBullet();
    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    Fire(Vector3 dir, float power, Vector3 rotation) override;


    //bool    GetIsFire() { return isFire; }
};
