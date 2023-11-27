#pragma once
class ItemBox : public ItemComponent
{
private:
	vector<ItemComponent*> items;
	//ItemComponent* items;
	
	// map<map<string, int> Item*> itemList; // string : key°ª, int : °¹¼ö, Item* °´Ã¼

	int itemLevel;		// 1 = normal  2 = rare


public:
	ItemBox();
	void Init();
	void add(ItemComponent* item);
	void list() const;
};

