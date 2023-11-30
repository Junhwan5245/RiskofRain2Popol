#pragma once
class ItemBox_Rare : public ItemBox
{
public:
	ItemBox_Rare();
	virtual ~ItemBox_Rare();
	void	Update() override;
	void	Render() override;
	void	CreateItem() override;

};

