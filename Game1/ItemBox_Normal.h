#pragma once
class ItemBox_Normal : public ItemBox
{
public:
	ItemBox_Normal();
	 ~ItemBox_Normal();
	void	Update() override;
	void	Render() override;
	void	CreateItem() override;
};



