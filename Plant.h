#ifndef _PLANT_H_
#define _PLANT_H_
#define HarvestTake 5.0f
#define WoodCut 3.0f
#define PlantMax 1
#include "ImmobileObject.h"
#include "Item.h"
#include <vector>
#include "LevelManager.h"

class Plant :
	public ImmobileObject
{
protected:
	float GrowCycle;
	float Plantcount = 0;
	bool DEAD = false;
	float GrowTime = 0;
	Object_List Product = _Max;
public:
	bool FinishGrow = false;
	Plant(Object_List Type);
	Plant(const Plant&obj);
	~Plant();

	Item* HarvestGrow();

	void Update(float Dtime);
	void Draw(XMMATRIX Pos);
	int RCSetup(Functionptr* f,ActionBtn* btn);

	Object * Interact(Jobs job, float Delta, Object* objinput = nullptr, Object_List make = _Max, int count = 0);
};

class CTree :
	public Plant
{
	bool soundonce = false;
	bool cangrow = false;
	std::vector<Item*> invenFruit;
public:
	CTree(Object_List list);
	CTree(Object_List list,Object::Position_and_Matrix p);
	~CTree();
	Item* HarvestApple();
	Item* CutWood();
	void Update(float Dtime);
	void Draw(XMMATRIX Pos);
	/*
	Description : Interact action with this object, doing all the jobs
	Return : Object*... If the job will return something, here you go.
	Parameter : 
	Jobs... What job
	float... Delta time
	Object*... Input Object for storing (Optional)
	Object_List... If job is making new item, what to make (Optional)
	P.S. : If job is storing, and it is not returning null, it means storing is not finish yet
	*/
	Object * Interact(Jobs job, float Delta, Object* objinput = nullptr, Object_List make = _Max, int count = 0);
	int RCSetup(Functionptr* f,ActionBtn* btn);
};
#endif