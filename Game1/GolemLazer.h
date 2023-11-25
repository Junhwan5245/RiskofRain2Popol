#pragma once
#pragma once
class GolemLazer : public Bullet
{
public:
    static GolemLazer* Create(string name = "GolemLazer");
private:

    GolemLazer();

public:
    virtual ~GolemLazer();
    void	Update() override;
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    Fire(Vector3 dir, float power, Vector3 rotation) override;


    //bool    GetIsFire() { return isFire; }
};

