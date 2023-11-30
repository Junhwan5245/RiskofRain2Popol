#pragma once
class Item_Feather : public Item
{
public:
    Item_Feather();
    virtual ~Item_Feather();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
};