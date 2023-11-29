#pragma once
enum NormalItemPool
{
	WALK,
	SizeNoraml
};

enum RareItemPool
{
	SYRINGE,
	SizeRare
};

class ItemBox
{
public:
	ItemBox();
	~ItemBox();
	Actor* itemBox;
	void			Init();
	virtual void	Update();
	virtual void	Render();
	virtual void	Operate();
	virtual void	Interaction();
	virtual	void	CreateItem();
	static ItemBox*		Create();
	
};

