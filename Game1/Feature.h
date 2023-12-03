#pragma once
class Feature
{
public:
    Feature();
    virtual ~Feature();
    virtual void	Update();
    virtual void	Render();
    virtual void    SetPosition();
    Actor* feature; 
    
};
