#pragma once

// Composite
class Item_Normal : public Item
{
private:
	vector<Item*> normalItems;
	string id;

public:
	Item_Normal(string i);
	void add(Item* item);
	void list() const;
};

