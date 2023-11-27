#pragma once
class Item3 : public Item
{
	friend class ItemComponent;
public:
	void Create();

	int s;
};

