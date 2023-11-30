#pragma once
class Item1 : public Item
{
public:
	Item1();
	~Item1();

	static Item1* Create(string itemName, int itemPrice, string itemGrade);

	int getPrice() const override {
		return price;
	}

	string getGrade() const override {
		return grade;
	}
};

