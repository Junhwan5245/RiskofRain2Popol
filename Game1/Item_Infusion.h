#pragma once
class Item_Infusion : public Item
{
public:
    Item_Infusion();
    virtual ~Item_Infusion();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
};