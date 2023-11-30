#include "stdafx.h"

Inventory::Inventory()
{
}

Inventory::~Inventory()
{
}

void Inventory::AddItem(string name)
{
    // find 함수를 사용하여 키가 이미 존재하는지 확인
    auto it = itemList.find(name);

    // 키가 이미 존재하지 않으면 추가
    if (it == itemList.end()) 
    {
        // 키가 존재하지 않는 경우, 새로운 아이템 추가
        itemList[name] = 1;
        cout << "아이템 '" << name << "'을(를) 추가했습니다." << endl;
    }
    else 
    {
        itemList[name]++;
        cout << "아이템 '" << name << "'의 개수는 " << itemList[name] << "개 입니다." << endl;
    }

    cout << "아이템 '" << name << "'가 삭제됩니다." << endl;
    GM->items.clear();
}
