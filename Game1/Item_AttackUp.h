#pragma once
class Item_AttackUp : public Item
{
public:
    Item_AttackUp();
    virtual ~Item_AttackUp();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
};

