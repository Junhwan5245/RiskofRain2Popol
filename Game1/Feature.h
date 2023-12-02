#pragma once
class Feature
{
public:
    Feature();
    virtual ~Feature();
    void    Init();
    virtual void	Update();
    virtual void	Render();
    virtual void    Set();
 
    Actor* feature; 
    
};
