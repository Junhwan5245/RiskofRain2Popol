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
	bool	isOpen;//���ڰ� �������ֳ�?
	bool	isFirst;//������ �ѹ��� �����ϱ����� bool
	float	openTime = 0.0f; //�ڽ� ��ȣ�ۿ� �� �ִϸ��̼� �뷫 ������ �ð� ���� Ÿ�̸�
	void			Init();
	virtual void	Update();
	virtual void	Render();
	virtual void	Operate();
	virtual void	Interaction();
	virtual	void	CreateItem();
	static ItemBox*		Create();
	
};

