#pragma once

// Component
class ItemComponent : public Actor
{
public:
	virtual int getPrice() const=0;
	virtual string getGrade() const=0;
	virtual void list() const = 0;
	virtual ~ItemComponent();
};