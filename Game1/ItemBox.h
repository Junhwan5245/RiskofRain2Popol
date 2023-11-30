#pragma once
enum NormalItemPool
{
	Syringe,
	APRound,
	Glasses,
	TriTipDagger,
	SizeNoraml
};

enum RareItemPool
{
	Feather,
	Infusion,
	Seed,
	AttackUp,
	DefendUp,
	SizeRare
};

class ItemBox
{
private:
	bool isOpen = false;


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

