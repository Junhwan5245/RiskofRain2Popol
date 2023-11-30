#pragma once
class Item : public ItemComponent
{
	friend class Item3;
private:
	//키값(이름)을 가지는 map하나 만들기

public:
	Item();
	void list() const;
};

