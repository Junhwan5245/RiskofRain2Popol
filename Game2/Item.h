#pragma once
class Item : public ItemComponent
{
	friend class Item3;
private:
	//Ű��(�̸�)�� ������ map�ϳ� �����

public:
	Item();
	void list() const;
};

