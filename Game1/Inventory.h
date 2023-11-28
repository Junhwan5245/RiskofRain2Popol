#pragma once
class Inventory
{
private:
	map<string, int> itemList;



public:
	Inventory();
	~Inventory();

	void AddItem(string name);
};

