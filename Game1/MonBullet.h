//#pragma once
//enum class MonBulletType
//{
//    LEMURIANBULLET
//};
//
//class MonBullet : public Bullet
//{
//public:
//    static MonBullet* Create(string name, MonsterType monType);
//
//protected:
//
//    MonBullet();
//    virtual ~MonBullet();
//public:
//    MonBulletType monBulletType;
//    MonsterType  monType;
//    void	Update();
//    void	Render(shared_ptr<Shader> pShader = nullptr);
//
//    void    SetPos(Vector3 pos) override;
//    void    Fire(Vector3 dir, float power, Vector3 rotation) override;
//
//    //bool    GetIsFire() { return isFire; }
//};
