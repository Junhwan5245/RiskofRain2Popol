#pragma once

// Component
class ItemComponent
{
	friend class Item;

public:
	virtual void list() const = 0;
	virtual ~ItemComponent();
};