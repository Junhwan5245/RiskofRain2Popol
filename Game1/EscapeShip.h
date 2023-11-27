#pragma once
class EscapeShip : public Actor
{
public:
    static EscapeShip* Create(string name = "EscapeShip");

private:

    EscapeShip();
    virtual ~EscapeShip();
public:

    void	Update();
    void	Render(shared_ptr<Shader> pShader = nullptr);
    void    SetPos();
};

