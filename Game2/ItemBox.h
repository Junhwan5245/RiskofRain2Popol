#pragma once
class ItemBox : public ItemComponent
{
private:
	vector<ItemComponent*> items;
	string id;

public:
	ItemBox(string i);
	void add(ItemComponent* item);
	void list() const;
};

