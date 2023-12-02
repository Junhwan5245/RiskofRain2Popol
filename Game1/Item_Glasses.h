#pragma once
class Item_Glasses : public Item
{
public:
    Item_Glasses();
    virtual ~Item_Glasses();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
};

