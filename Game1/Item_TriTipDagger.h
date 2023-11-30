#pragma once
class Item_TriTipDagger : public Item
{
public:
    Item_TriTipDagger();
    virtual ~Item_TriTipDagger();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
};

