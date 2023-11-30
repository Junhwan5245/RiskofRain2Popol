#pragma once
class Item_Seed : public Item
{
public:
    Item_Seed();
    virtual ~Item_Seed();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
};