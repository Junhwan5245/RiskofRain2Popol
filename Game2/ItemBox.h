#pragma once
class ItemBox : public ItemComponent
{
private:
	vector<ItemComponent*> items;
	/*string id;*/

public:
	ItemBox();
	void add(ItemComponent* item);
	void list() const;
	void Update();
	void Render();
	void Interection();//��ȣ�ۿ��Լ�
};

