#include "stdafx.h"

Item_APRound::Item_APRound()
{
	item->LoadFile("Item_APRound.xml");
	item->name = "APRound";
	itemType = ItemType::NORMAL;
}

Item_APRound::~Item_APRound()
{
}

void Item_APRound::Operate()
{//보스에게 20%(중첩당 +20%) 추가 피해

}

void Item_APRound::Update()
{
	Item::Update();
}

void Item_APRound::Render()
{
	Item::Render();
}
