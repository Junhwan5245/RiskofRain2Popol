//#include "stdafx.h"
//
//MonBullet* MonBullet::Create(string name, MonsterType monType)
//{
//    MonBullet* temp = nullptr;
//
//    switch (monType)
//    {
//    case MonsterType::BEETLE:
//        return temp;
//        break;
//
//    case MonsterType::LEMURIAN:
//        temp = LemurianBullet::Create(name);
//        break;
//
//    default:
//        return temp;
//        break;
//    }
//}
//
//MonBullet::MonBullet()
//{
//}
//
//MonBullet::~MonBullet()
//{
//}
//
//void MonBullet::Update()
//{
//    Bullet::Update();
//}
//
//void MonBullet::Render(shared_ptr<Shader> pShader)
//{
//    Bullet::Render(pShader);
//}
//
//void MonBullet::SetPos(Vector3 pos)
//{
//    Bullet::SetPos(pos);
//}
//
//void MonBullet::Fire(Vector3 dir, float power, Vector3 rotation)
//{
//    Bullet::Fire(dir, power, rotation);
//}
