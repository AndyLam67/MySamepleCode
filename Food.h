#ifndef _FOOD_H_
#define _FOOD_H_
#include "Item.h"
#include "Content.h"
class Colonist;
class Food :
	public Item
{
	int Boost;
public:
	Food(Object_List type,int boost,Recipe one);
	Food(const Food&obj);
	~Food();
	int GetHungryboost() { return Boost; }
	void Eat(Colonist* col);
	Object* Interact(Jobs job, float Delta, Object* objinput= nullptr, Object_List make = _Max, int count = 0);
	int RCSetup(Functionptr* f,ActionBtn* btn);
};
#endif // !_FOOD_H_
