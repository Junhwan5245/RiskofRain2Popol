#pragma once
class Item_Rare : public ItemComponent
{
private:
	vector<ItemComponent*> rareItems;
	string id;

public:
	Item_Rare(string i);
	void add(ItemComponent* item);
	void list() const;
};

