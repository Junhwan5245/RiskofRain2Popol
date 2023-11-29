#pragma once
class ItemBox : public ItemComponent
{
private:
	vector<ItemComponent*> items;
	//ItemComponent* items;
	
	// map<map<string, int> Item*> itemList; // string : key값, int : 갯수, Item* 객체

	int itemLevel;		// 1 = normal  2 = rare


public:
	ItemBox();
	void Init();
	void add(ItemComponent* item);
	void list() const;
	void Update();
	void Render();
	void Interection();//상호작용함수
};

