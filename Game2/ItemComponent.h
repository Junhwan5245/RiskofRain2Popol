#pragma once

// Component
class ItemComponent
{
public:
	virtual void list() const = 0;
	virtual ~ItemComponent();
};