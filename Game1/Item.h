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
    virtual void    Operate();//������ ȿ���ߵ�
    virtual void    Interaction();//������ ��ȣ�ۿ�
   
};



