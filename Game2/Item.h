#pragma once
class Item : public ItemComponent
{
	friend class Item3;
private:
	int value;

public:
	Item();
	void list() const;
};

