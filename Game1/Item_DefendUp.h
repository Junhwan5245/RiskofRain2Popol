#pragma once
class Item_DefendUp : public Item
{
public:
    Item_DefendUp();
    virtual ~Item_DefendUp();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
};

