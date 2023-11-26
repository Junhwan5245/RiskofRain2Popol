#pragma once
class BossBullet2 : public Bullet
{
    public:
        static BossBullet2* Create(string name = "BossBullet2");
    private:
        BossBullet2();
        float exploreTime;
        bool  isExplore = false;
    public:
        virtual ~BossBullet2();
        void	Update() override;
        void	Render(shared_ptr<Shader> pShader = nullptr);
        void    Fire(Vector3 dir, float power, Vector3 rotation) override;
};

