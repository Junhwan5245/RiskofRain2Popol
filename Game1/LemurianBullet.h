#pragma once
class LemurianBullet : public Bullet
{
public:
    static LemurianBullet* Create(string name = "LemurianBullet");
private:
    LemurianBullet();
    
public:
    virtual ~LemurianBullet();
    class LemurianBulletTrail* trail;
    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    Fire(Vector3 dir, float power, Vector3 rotation) override;
    

    //bool    GetIsFire() { return isFire; }
};
