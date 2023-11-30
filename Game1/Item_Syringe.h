#pragma once
class Item_Syringe : public Item
{ 
public:
    Item_Syringe();
    virtual ~Item_Syringe();
    void	Operate()   override;
    void	Update()    override;
    void	Render()    override;
   
};


