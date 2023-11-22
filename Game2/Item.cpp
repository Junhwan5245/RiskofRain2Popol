#include "stdafx.h"

Item::Item(int v) : value(v)
{
}

void Item::list() const
{
	cout << value << endl;
}
