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
	Actor*	itemBox;
	bool	isOpen;//상자가 열린적있나?
	bool	isFirst;//아이템 한번만 생성하기위한 bool
	float	openTime = 0.0f; //박스 상호작용 후 애니메이션 대략 끝나는 시간 위한 타이머
	void			Init();
	virtual void	Update();
	virtual void	Render();
	virtual void	Operate();
	virtual void	Interaction();
	virtual	void	CreateItem();
	static ItemBox*		Create();
	
};

