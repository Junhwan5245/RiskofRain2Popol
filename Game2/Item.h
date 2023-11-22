#pragma once
class Item : public ItemComponent
{
private:
	int value;

public:
	Item(int v);
	void list() const;
};

