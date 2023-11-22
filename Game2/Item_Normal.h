#pragma once

// Composite
class Item_Normal : public ItemComponent
{
private:
	vector<ItemComponent*> normalItems;
	string id;

public:
	Item_Normal(string i);
	void add(ItemComponent* item);
	void list() const;
};

