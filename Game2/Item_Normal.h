#pragma once

// Composite
class Item_Normal : public ItemComponent
{
private:
	vector<ItemComponent*> normalItems;
	

public:
	Item_Normal();
	void add(ItemComponent* item);
	void list() const;
};

