#pragma once

// Composite
class Item_Normal : public ItemComponent
{
	friend class Item;

private:
	map<string, ItemComponent*> normalItems; // string : naem(key)




public:
	Item_Normal();
	void Init();
	void add(ItemComponent* item);
	void list() const;


};

