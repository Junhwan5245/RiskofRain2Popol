#pragma once

// Component
class ItemComponent : public Actor
{
	friend class Item;

public:
	virtual int getPrice() const=0;
	virtual string getGrade() const=0;
	virtual void list() const = 0;
	virtual ~ItemComponent();
};