#pragma once
enum class ItemType
{
    NORMAL,
    RARE
};

class Item 
{
public:
    Actor* item;
    ItemType itemType;

    Item();
    virtual ~Item();
    virtual void	Update();
    virtual void	Render();
    virtual void    Operate();//아이템 효과발동
    virtual void    Interaction();//아이템 상호작용
   
};



