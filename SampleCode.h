#pragma region README
// For my final project in college, I make our own game engine with a group of programmers. 
// I created the Game Object Manager, to help my teammate to instantiate, destroy, and handle all the game objects.
// I also created all the game object related classes. 
// I created a parent GameObject class, then inheritance into 2 groups, "MobileObjects" and"ImmobileObjects". 
// After that I inheritance all the child class from this 2 big group. 
// 
// I am not sure what kind of sample code should I show, so I am giving you my whole GameObject Manager, my GameObject parent class, and two of my child class. 
// Please ask me anything if you have any question about my code. Thank you!
#pragma endregion

#pragma region Object.h
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include <DirectXMath.h>
#include <vector>
#include <iostream>
#include "Content.h"
#include "WWise/WWise_Audio.h"
//#include "ObjectManager.h"
class Object;
class Weapon;
class ObjectManager;
class LevelManager;
class Colonist;
#define GameTest 0
#define PosX Pos_n_Matrix.Pos.X
#define PosY Pos_n_Matrix.Pos.Y
#define PosZ Pos_n_Matrix.Pos.Z
typedef void(Object::*Functionptr)(Colonist*);
using namespace DirectX;
using namespace std;
enum Jobs
{
	None = 0,
	Planting,
	Farming,
	Woodcutting,
	Hauling,
	Mining,
	Hunting,
	Cooking,
	Exploring,
	Construction,
	Smithing,
	Alchemy,
	Storing,
	Pickup,
	Consuming,  //eating food and using furniture
	GearUp,
	_MaxJobs
};
class Object
{
protected:
	bool JobFlag = false;
	Colonist* JobClaim = nullptr;
	Jobs Currjob = Jobs::None;
	ObjectManager* OM;
	LevelManager* LM;
	Object_List Type;
	int meshindex;
public:
	float DTime = 0;
	WWise_Audio Waudio;
	bool Visible = true;
	bool FgLooking = false;
	bool FgPickup = false;
	bool ShowText = false;
	float Texttime = 0.0f;
	ItemState ItemState = OnGround;
	Object* BelongsTo = nullptr;
	Object();
	Object(Object_List type);
	Object(const Object&obj);
	virtual ~Object();
	//Position in tilemap
	struct Pos
	{
		Pos() { X = 0, Y = 0, Z = 0; }
		Pos(int x, int y, int z) { x = X; y = Y, z = Z; }
		int X, Y, Z;
	};
	struct Offset
	{
		float X = 0, Z = 0;
	};
	struct Position_and_Matrix
	{
		Pos Pos;
		Offset Offset;
		//Matrix in Render Space, contains Position, Rotation, and scaling
		XMMATRIX Matrix = XMMATRIX();
	};
	Position_and_Matrix Pos_n_Matrix;

	/*
	Description :
	Return : void
	Parameter : void
	*/
	bool IsFlagForJob() { return JobFlag; }
	/*
	Description :
	Return : void
	Parameter : void
	*/
	Jobs GetJob() { return Currjob; }
	/*
	Description :
	Return : void
	Parameter : void
	*/
	void SetJob(Jobs job);
	/*
	Description : Call for render
	Return : void
	Parameter : void
	*/
	virtual void Draw(XMMATRIX Pos);// = 0;

	void SetLevelManager(LevelManager* lm) { LM = lm; }
	void SetObjectManager(ObjectManager* om) { OM = om; }

	virtual void Update(float Dtime);
	/*
	Description : Check if this object is specific type
	Return : bool...true if same type, false otherwise
	Parameter : type...type that checking
	*/
	template<class T>
	bool IsType(T type);

	Object_List GetObjectType() { return Type; }

	void SetDeltaTime(float t) { DTime = t; }

	Colonist* GetJobClaim() { return JobClaim; }

	void SetJobClaim(Colonist* t) { JobClaim = t; }

	void GetNameinCP(char*& out);
	virtual Object* Interact(Jobs job, float Delta, Object* objinput= nullptr, Object_List make = _Max, int count = 0);
	virtual int RCSetup(Functionptr* f,ActionBtn* btn);
#pragma region RightClick Functions
	void FnHauling(Colonist* col);
	void FnHarvest(Colonist* col);
	void FnWoodCutting(Colonist* col);
	void FnMining(Colonist* col);
	void FnConsuming(Colonist* col);
	void FnStoring(Colonist* col);
	void FnHunting(Colonist* col);
	void FnCrash(Colonist* col);
	void FnDestroy(Colonist* col);
	void FnPickUp(Colonist* col);
	void FnGearUp(Colonist* col);
	void FnGear(Colonist* col);
	void FnUngear(Colonist* col);
	void FnUnlock(Colonist* col);
	void FnHarvestFarmLand(Colonist* col);
	void FnDestroyOBJ(Colonist* col);
#pragma endregion
};

template<class T>
inline bool Object::IsType(T type)
{
	//return dynamic_cast<type*>(this) == 0 ? true : false;
}
#endif // !_OBJECT_H_

#pragma endregion

#pragma region Object.cpp
#include "stdafx.h"
#include "Object.h"
#include "Tools.h"
#include "Colonist.h"
#include "ObjectManager.h"
#include "LevelManager.h"
#include "Chests.h"
#include "LvDoor.h"
#include "Food.h"
#include "Plant.h"
#include "Potion.h"
#include "MiningRocks.h"

Object::Object()
{
}

Object::Object(Object_List type)
{
	Type = type;
	DTime = 0;
}

Object::Object(const Object & obj)
{
	this->Currjob = obj.Currjob;
	this->DTime = obj.DTime;
	this->JobFlag = obj.JobFlag;
	this->LM = obj.LM;
	this->OM = obj.OM;
	this->Pos_n_Matrix = obj.Pos_n_Matrix;
	this->Type = obj.Type;
	this->Visible = obj.Visible;
	this->meshindex = obj.meshindex;
	DTime = 0;
}

Object::~Object()
{
}

void Object::SetJob(Jobs job)
{
	OM->ApplyJob(this, job);
	Currjob = job;
	Currjob == Jobs::None ? JobFlag = false : JobFlag = true;
}

void Object::Draw(XMMATRIX Pos)
{
	if (this->Visible == true)
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, Pos);
}

void Object::Update(float Dtime)
{
	//this->DTime += Dtime;
}

void Object::GetNameinCP(char *& out)
{
	switch (Type)
	{
	case _Resources:
		break;
	case Log:
	{
		char n[] = "Log";
		out = new char[4];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Plank:
	{
		char n[] = "Plank";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Stick:
	{
		char n[6] = "Stick";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Stone:
	{
		char n[6] = "Stone";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Brick:
	{
		char n[6] = "Brick";
		out = new char[5];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case GoldenCoin:
	{
		char n[] = "Golden Coin";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperOre:
	{
		char n[] = "CopperOre";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronOre:
	{
		char n[] = "IronOre";
		out = new char[8];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Coal:
	{
		char n[5] = "Coal";
		out = new char[5];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilOre:
	{
		char n[] = "MithrilOre";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumOre:
	{
		char n[] = "OrichalcumOre";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantOre:
	{
		char n[] = "AdamantOre";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumOre:
	{
		char n[] = "PromethiumOre";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperBar:
	{
		char n[] = "CopperBar";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronBar:
	{
		char n[] = "IronBar";
		out = new char[8];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelBar:
	{
		char n[] = "SteelBar";
		out = new char[9];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilBar:
	{
		char n[] = "MithrilBar";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumBar:
	{
		char n[] = "OrichalcumBar";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantBar:
	{
		char n[] = "AdamantBar";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumBar:
	{
		char n[] = "PromethiumBar";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _Food:
		break;
	case RawMeat:
	{
		char n[] = "Raw Meat";
		out = new char[9];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CookedMeat:
	{
		char n[] = "Cooked Meat";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Apple:
	{
		char n[] = "Apple";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Wheat:
	{
		char n[] = "Wheat";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Potato:
	{
		char n[] = "Potato";
		out = new char[7];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Beans:
	{
		char n[] = "Beans";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
#pragma region Plant
	case Wolfsbane:
	{
		char n[] = "Wolfsbane";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Dandelion:
	{
		char n[] = "Dandelion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Marigold:
	{
		char n[] = "Marigold";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Rosemary:
	{
		char n[] = "Rosemary";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Mushroom:
	{
		char n[] = "Mushroom";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Feybell:
	{
		char n[] = "Feybell";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Deeproot:
	{
		char n[] = "Deeproot";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Clover:
	{
		char n[] = "Clover";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
#pragma endregion
#pragma region Potions
	case AttackPotion:
	{
		char n[] = "Attack Potion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SpeedPotion:
	{
		char n[] = "Speed Potion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case HealingPotion:
	{
		char n[] = "Healing Potion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case DefensePotion:
	{
		char n[] = "Defense Potion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IntelligencePotion:
	{
		char n[] = "Intelligence Potion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CarryingPotion:
	{
		char n[] = "Carrying Potion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case LuckPotion:
	{
		char n[] = "Luck Potion";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
#pragma endregion

	case _Tool:
		break;
	case WoodenSword:
	{
		char n[] = "WoodenSword";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WoodenShield:
	{
		char n[] = "WoodenShield";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WoodenBow:
	{
		char n[] = "WoodenBow";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WoodenArrow:
	{
		char n[] = "WoodenArrow";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WoodenAxe:
	{
		char n[] = "WoodenAxe";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WoodenPickaxe:
	{
		char n[] = "WoodenPickaxe";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WoodenHoe:
	{
		char n[] = "WoodenHoe";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WoodenHammer:
	{
		char n[] = "WoodenHammer";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case StoneSword:
	{
		char n[] = "StoneSword";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case StoneShield:
	{
		char n[] = "StoneShield";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case StoneArrow:
	{
		char n[] = "StoneArrow";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case StoneAxe:
	{
		char n[] = "StoneAxe";
		out = new char[9];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case StonePickaxe:
	{
		char n[] = "StonePickaxe";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case StoneHoe:
	{
		char n[] = "StoneHoe";
		out = new char[9];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case StoneHammer:
	{
		char n[] = "StoneHammer";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperSword:
	{
		char n[] = "CopperSword";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperShield:
	{
		char n[] = "CopperShield";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperArrow:
	{
		char n[] = "CopperArrow";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperAxe:
	{
		char n[] = "CopperAxe";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperPickaxe:
	{
		char n[] = "CopperPickaxe";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperHoe:
	{
		char n[] = "CopperHoe";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case CopperHammer:
	{
		char n[] = "CopperHammer";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronSword:
	{
		char n[] = "IronSword";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronShield:
	{
		char n[] = "IronShield";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronArrow:
	{
		char n[] = "IronArrow";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronAxe:
	{
		char n[] = "IronAxe";
		out = new char[8];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronPickaxe:
	{
		char n[] = "IronPickaxe";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronHoe:
	{
		char n[] = "IronHoe";
		out = new char[8];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case IronHammer:
	{
		char n[] = "IronHammer";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelSword:
	{
		char n[] = "SteelSword";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelShield:
	{
		char n[] = "SteelShield";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelArrow:
	{
		char n[] = "SteelArrow";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelAxe:
	{
		char n[] = "SteelAxe";
		out = new char[9];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelPickaxe:
	{
		char n[] = "SteelPickaxe";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelHoe:
	{
		char n[] = "SteelHoe";
		out = new char[9];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case SteelHammer:
	{
		char n[] = "SteelHammer";
		out = new char[12];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilSword:
	{
		char n[] = "MithrilSword";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilShield:
	{
		char n[] = "MithrilShield";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilArrow:
	{
		char n[] = "MithrilArrow";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilAxe:
	{
		char n[] = "MithrilAxe";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilPickaxe:
	{
		char n[] = "MithrilPickaxe";
		out = new char[15];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilHoe:
	{
		char n[] = "MithrilHoe";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MithrilHammer:
	{
		char n[] = "MithrilHammer";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumSword:
	{
		char n[] = "OrichalcumSword";
		out = new char[16];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumShield:
	{
		char n[] = "OrichalcumShield";
		out = new char[17];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumArrow:
	{
		char n[] = "OrichalcumArrow";
		out = new char[16];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumAxe:
	{
		char n[] = "OrichalcumAxe";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumPickaxe:
	{
		char n[] = "OrichalcumPickaxe";
		out = new char[18];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumHoe:
	{
		char n[] = "OrichalcumHoe";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case OrichalcumHammer:
	{
		char n[] = "OrichalcumHammer";
		out = new char[17];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantSword:
	{
		char n[] = "AdamantSword";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantShield:
	{
		char n[] = "AdamantShield";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantArrow:
	{
		char n[] = "AdamantArrow";
		out = new char[13];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantAxe:
	{
		char n[] = "AdamantAxe";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantPickaxe:
	{
		char n[] = "AdamantPickaxe";
		out = new char[15];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantHoe:
	{
		char n[] = "AdamantHoe";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case AdamantHammer:
	{
		char n[] = "AdamantHammer";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumSword:
	{
		char n[] = "PromethiumSword";
		out = new char[16];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumShield:
	{
		char n[] = "PromethiumShield";
		out = new char[17];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumArrow:
	{
		char n[] = "PromethiumArrow";
		out = new char[16];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumAxe:
	{
		char n[] = "PromethiumAxe";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumPickaxe:
	{
		char n[] = "PromethiumPickaxe";
		out = new char[18];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumHoe:
	{
		char n[] = "PromethiumHoe";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PromethiumHammer:
	{
		char n[] = "PromethiumHammer";
		out = new char[17];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _Sources:
		break;
	case FTree:
	{
		char n[] = "Fruit Tree";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PTree:
	{
		char n[] = "Pine Tree";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PSTree:
	{
		char n[] = "Pine Tree";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WheatFarm:
	{
		char n[] = "Wheat";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PotatoFarm:
	{
		char n[] = "Potato";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case BeansFarm:
	{
		char n[] = "Beans";
		out = new char[sizeof(n)];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _MiningRock:
		break;
	case MRStone:
	{
		char n[] = "Stone";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MRCopper:
	{
		char n[] = "CopperOre";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MRIron:
	{
		char n[] = "IronOre";
		out = new char[8];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MRCoal:
	{
		char n[] = "Coal";
		out = new char[5];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MRMithril:
	{
		char n[] = "MithrilOre";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MROrichalcum:
	{
		char n[] = "OrichalcumOre";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MRAdamant:
	{
		char n[] = "AdamantOre";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case MRPromethium:
	{
		char n[] = "PromethiumOre";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _Buildings:
		break;
	case AlchemyTable:
	{
		char n[] = "Alchemy Table";
		out = new char[14];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Forge:
	{
		char n[6] = "Forge";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Kitchen:
	{
		char n[] = "Kitchen";
		out = new char[8];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case WorkBench:
	{
		char n[11] = "Work Bench";
		out = new char[11];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _ConstructionLand:
	{
		char n[] = "In Construction";
		out = new char[16];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Wall:
	{
		char n[] = "Wall";
		out = new char[5];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Chest:
	{
		char n[] = "Chest";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case lvDoor:
	{
		char n[] = "Staircase";
		out = new char[10];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case PortalKey:
	{
		char n[] = "Key";
		out = new char[4];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _MobileObject:
		break;
	case _Colonist:
		break;
	case _Enemy:
		break;
	case Slime:
	{
		char n[] = "Slime";
		out = new char[6];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Wolf:
	{
		char n[] = "Wolf";
		out = new char[5];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Skeleton:
	{
		char n[] = "Skeleton";
		out = new char[9];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _Animal:
		break;
	case Cow:
	{
		char n[] = "Cow";
		out = new char[4];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Chicken:
	{
		char n[] = "Chicken";
		out = new char[8];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case Pig:
	{
		char n[] = "Pig";
		out = new char[4];
		strncpy_s(out, sizeof(n), n, sizeof(n));
		break;
	}
	case _Max:
		break;
	default:

		break;
	}
}

Object * Object::Interact(Jobs job, float Delta, Object* objinput, Object_List make, int count)
{
	Object* result = nullptr;
	if (GetJob() == job)
	{
		switch (job)
		{
		case Hauling:
		{
			result = this;
			this->Visible = false;
			LM->GetTileMap()->GetTile(this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Z)->SetImmobileObject(nullptr);
			break;
		}
		default:
			this->DTime = 0;
			break;
		}
	}
	return result;
}

int Object::RCSetup(Functionptr* f, ActionBtn* btn)
{
	//f[0] = &Object::FnHauling;
	//f[1] = &Object::FnHarvest;
	//f[2] = &Object::FnWoodCutting;
	//f[3] = &Object::FnMining;
	//return 4;
	cout << "no function set" << endl;
	return 0;
}

void Object::FnHauling(Colonist * col)
{
	SetJob(Hauling);
	if (col)
	{
		col->SetCurrentJob(Jobs::Hauling);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
		SetJobClaim(col);
	}
}

void Object::FnHarvest(Colonist * col)
{
	SetJob(Farming);
	if (col)
	{
		col->SetCurrentJob(Jobs::Farming);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
		SetJobClaim(col);
	}
}

void Object::FnWoodCutting(Colonist * col)
{
	SetJob(Woodcutting);
	if (col)
	{
		col->SetCurrentJob(Jobs::Woodcutting);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
		SetJobClaim(col);
	}
}

void Object::FnMining(Colonist * col)
{
	SetJob(Mining);
	if (col)
	{
		if (col->GetMining_gear())
		{
			if (col->GetMining_gear()->GetMakeType()+2 > ((MiningRocks*)this)->GetRockType())
			{

				col->SetCurrentJob(Jobs::Mining);
				col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
				SetJobClaim(col);

			}
			else
			{
				NotificationManager::Notification message;
				message.type = NotificationManager::NType::Notify;
				message.message = new char[42];
				message.x = PosX;
				message.y = PosY;
				message.z = PosZ;
				char msg[] = "A better pickaxe is needed for mining job";
				for (unsigned int i = 0; i < 42; i++)
					message.message[i] = msg[i];
				LM->GetNotificationManager()->PostNotification(message, 15.0f);
				SetJob(None);
			}
		}
		else
		{
			NotificationManager::Notification message;
			message.type = NotificationManager::NType::Notify;
			message.message = new char[35];
			message.x = PosX;
			message.y = PosY;
			message.z = PosZ;
			char msg[] = "A pickaxe is needed for mining job";
			for (unsigned int i = 0; i < 35; i++)
				message.message[i] = msg[i];
			LM->GetNotificationManager()->PostNotification(message, 15.0f);
			SetJob(None);
		}
	}
}

void Object::FnConsuming(Colonist * col)
{
	if (col)
	{
		Potion* pot = dynamic_cast<Potion*>(this);
		Food* fod = dynamic_cast<Food*>(this);
		if (fod)
		{
			col->GetBackPack()->RetrieveItem(fod);
			fod->Eat(col);
		}
		else if (pot)
		{
			col->GetBackPack()->RetrieveItem(pot);
			pot->DrinkPotion(col);
		}
	}
}

void Object::FnStoring(Colonist * col)
{
	SetJob(Storing);
	if (col)
	{
		col->SetCurrentJob(Jobs::Storing);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
	}
}

void Object::FnHunting(Colonist * col)
{
	SetJob(Hunting);
	if (col)
	{
		col->SetCurrentJob(Jobs::Hunting);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
		SetJobClaim(col);
	}
}

void Object::FnCrash(Colonist * col)
{
	if (col)
	{
		col->SetCurrentJob(Jobs::Pickup);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
		SetJobClaim(col);
	}
}

void Object::FnDestroy(Colonist * col)
{
	if (col)
	{
		Item* trys = col->GetBackPack()->RetrieveItem((Item*)this);
		OM->Destroy(this);
	}
}

void Object::FnPickUp(Colonist * col)
{
	if (col)
	{
		col->SetCurrentJob(Jobs::Pickup);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
		SetJobClaim(col);
	}
}

void Object::FnGearUp(Colonist * col)
{
	Chests* chest = dynamic_cast<Chests*>(BelongsTo);
	Backpack* bp = dynamic_cast<Backpack*>(BelongsTo);
	if (chest)
	{
		if (col)
		{
			this->FgPickup = true;
			chest->NewRequest(this->Type, col);
		}
	}
	else if (bp)
	{
		if (col)
		{
			this->FgPickup = true;
			bp->NewRequest(this->Type, col);
		}
	}
}

void Object::FnGear(Colonist * col)
{
	Armory* armor = dynamic_cast<Armory*>(this);
	Tools* tools = dynamic_cast<Tools*>(this);

	if (armor)
	{
		Armory* oldA = col->GetArmor_Gear();
		if (oldA)
		{
			oldA->ItemState = InInven;
			col->AddBackPackItem(oldA);
		}
		armor->ItemState = equiped;
		col->SetArmor_Gear(armor);
		col->SetArmor(armor->GetArmor());
	}
	else if (tools)
	{
		if (tools->GetWeaponType() == Pickaxe)
		{
			Tools* oldA = col->GetMining_gear();
			if (oldA)
			{
				oldA->ItemState = InInven;
				col->AddBackPackItem(oldA);
			}
			tools->ItemState = equiped;
			col->SetMining_gear(tools);
		}
		else
		{
			Tools* oldA = col->GetWeapon();
			if (oldA)
			{
				oldA->ItemState = InInven;
				col->AddBackPackItem(oldA);
			}
			tools->ItemState = equiped;
			col->SetWeapon(tools);
			col->SetDamage(tools->GetDmg());
		}
	}
	else
	{

	}
	col->GetBackPack()->RetrieveItem((Item*)this);
}

void Object::FnUngear(Colonist * col)
{
	if (this == col->GetArmor_Gear())
	{
		col->SetArmor_Gear(nullptr);
		col->AddBackPackItem((Item*)this);
		col->SetArmor(col->GetArmor() - ((Armory*)this)->GetArmor());
		this->ItemState = InInven;
	}
	if (this == col->GetMining_gear())
	{
		col->SetMining_gear(nullptr);
		col->AddBackPackItem((Item*)this);
		this->ItemState = InInven;
	}
	if (this == col->GetWeapon())
	{
		col->SetWeapon(nullptr);
		col->AddBackPackItem((Item*)this);
		col->SetDamage(col->GetDamage() - ((Tools*)this)->GetDmg());
		this->ItemState = InInven;
	}
}

void Object::FnUnlock(Colonist * col)
{
	((Key*)this)->UnlockDoor();
}

void Object::FnHarvestFarmLand(Colonist * col)
{
	SetJob(Farming);
	if (col)
	{
		col->SetCurrentJob(Jobs::Farming);
		col->GetAIManger()->SetColonistDestination(col, LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z));
		SetJobClaim(col);
	}
}

void Object::FnDestroyOBJ(Colonist * col)
{
	LM->GetTileMap()->GetTile(PosY,PosX,PosZ)->SetImmobileObject(nullptr);
	OM->Destroy(this);
}

#pragma endregion

#pragma region ObjectManager.h
#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_
#include "Object.h"
#include "Content.h"
#include <vector>
#include <unordered_map>
#pragma region classes
class GraphicsManager;
class AI;
class Animal;
class ImmobileObject;
class Item;
class LevelManager;
class Colonist;
class Chests;
class Request;
class Backpack;
#pragma endregion
enum obj_type
{
	_otColonist = 0, _otAnimals, _otEnemies, _otSources,
	_otResources, _otBuildings, _otItems, _otChest, _otWalls,
	_otDoors,
	_otStone,
	_otMAX
};
struct ChestCon
{
	Object_List type = _Max;
	int count = 0;
};
class ObjectManager
{
	GraphicsManager* GM;
	AI* AIM;
	LevelManager* LM;
	unsigned int ObjectCounter[Object_List::_Max];
	std::vector<Object*> LiveObjectList[_otMAX]; //used to store all the living object that currenty in the game
	std::vector<Object*> JobList[Jobs::_MaxJobs]; //used to store all living object that tag for jobs.
	std::vector<Request*> LiveRequestList; //used to store all the living request from all work places
	std::unordered_map < Object_List, Object* > ObjectList; //used to store all the object in the game. Initial when the game start.
	std::vector<Object*> Trash;
	void ObjectListInit();
	Object* CheckTile(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count);
	Object* CheckTile2(unsigned int x, unsigned int y, unsigned int z, Object_List item);
protected:
	int Unlockedlv = 0;
	float Difficulty = 1.0f;
public:
	ObjectManager();
	~ObjectManager();
	/*
	Description : Call when Initial the program
	Return : void
	Parameter : void
	*/
	void Initial(GraphicsManager* gm, AI* aim, LevelManager* lm);
	void EndGame();
	void NewGame();
	/*
	Description : Destroy specific object from the object list
	Return : bool...true if success, false if fail for some reason
	Parameter : object...the object want to delete
	*/
	bool Destroy(Object* object);
	/*
	Description : Call when shut down the program
	Return : void
	Parameter : void
	*/
	void Shutdown();
	/*
	Description : Update
	Return : void
	Parameter : float...delta time
	*/
	void Update(float Dtime);
	/*
	Description : Get Object description
	Return : Object*...Object instantiate
	Parameter : Object_List...what item you are looking for
	*/
	Object* GetObj(Object_List obj) { return ObjectList[obj]; }
	/*
	Description : Call when want to create a living object
	Return : Object*...Pointer of living object
	Parameter :
	Object_List...Type of object
	XMMATRIX...World matrix of new object
	uintX...Tile X position
	uintY...Tile Y level
	uintZ...Tile Z position
	*/
	Object* Create(Object_List Type, XMMATRIX Matrix, int x, int y, int z);
	/*
	Description : Call when want to create a living object
	Return : Object*...Pointer of new living object
	Parameter : Object*...Pointer of old living object
	*/
	Object* Create(Object* object);
	Object* Create(Object* object, Object::Position_and_Matrix pnm);
	/*
	Description :
	Return : void
	Parameter : void
	*/
	void ApplyJob(Object* object, Jobs job);
	/*
	Description : Search the closest availabe object that required specific job be done by the giving position
	Return : Object*...the closest object
	Parameter :
	Uint...Target x position
	Uint...Target y position
	Uint...Target z position
	Jobs...Jobs that looking for
	*/
	Object* FindJob(Jobs looking, Colonist* col);
	/*
	Description : Search the closest colonist by the giving position
	Return : Colonist*...the closest colonist
	Parameter :
	Uint...Target x position
	Uint...Target y position
	Uint...Target z position
	*/
	Colonist* FindColonist(unsigned int x, unsigned int y, unsigned int z);
	Animal* FindAnimal(unsigned int x, unsigned int y, unsigned int z);
	/*
	Description : Search the closest chest contain certain item by the giving position
	Return : Chest*...the closest Chest
	Parameter :
	Uint...Target x position
	Uint...Target y position
	Uint...Target z position
	Object_List...What item
	int...How many
	*/
	Chests* FindChest(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count);
	/*
	Description : Search the closest ground contain certain item by the giving position
	Return : Object*...the closest Object
	Parameter :
	Uint...Target x position
	Uint...Target y position
	Uint...Target z position
	Object_List...What item
	int...How many
	*/
	Object* FindObjectOntheGround(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count);
	Object* FindClosestObject(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count);
	Object* FindLiveObject(unsigned int x, unsigned int y, unsigned int z, Object_List item);


	Object* FindObjectOntheGround2(unsigned int x, unsigned int y, unsigned int z, Object_List item);
	Object* FindClosestObject2(unsigned int x, unsigned int y, unsigned int z, Object_List item);
	Object* FindChest2(unsigned int x, unsigned int y, unsigned int z, Object_List item);
	Object* FindColonistWithObject(unsigned int x, unsigned int y, unsigned int z, Object_List item);

	//true = up, false = down
	Object* FindStaircase(Colonist* col, bool up);

	Request* FindRequest(Colonist* col);

	bool InitRequest(Request* req, Object::Position_and_Matrix pos);
	/*
	Description :
	Return : void
	Parameter : void
	*/
	ObjectManager* GetOM() { return this; }
	/*
	Description :
	Return : void
	Parameter : void
	*/
	GraphicsManager* GetGM() { return GM; }
	LevelManager* GetLM() { return LM; }

	bool AddRequest(Request* recipe);

	bool RemoveRequest(Request* recipe);

	int GetCurrentColonistCount();

	int GetCurrentEnemyCount();  

	void Colonist_DeathInform(Colonist* col);

	void AddBackPacktoArray(Backpack* bp);

	void UpdateUnlockedLayer(int lv);

	void UpdateDifficulty(float lv);

	int GetUnlockedLv() { return Unlockedlv; }

	unsigned int GetObjectCount(Object_List type);

	vector<Object*> GetLiveColonistList();

	vector<ChestCon> GetChestContent();
};

#endif // !_OBJECTMANAGER_H_

#pragma endregion

#pragma region ObjectManager.cpp
#include "stdafx.h"
#include "Animal.h"
#include "Armory.h"
#include "Backpack.h"
#include "Building.h"
#include "Chests.h"
#include "Colonist.h"
#include "ConstructionLand.h"
#include "Enemy.h"
#include "Farmland.h"
#include "Food.h"
#include "LvDoor.h"
#include "MiningRocks.h"
#include "ObjectManager.h"
#include "Obstacle.h"
#include "Plant.h"
#include "Request.h"
#include "Tools.h"
#include "Potion.h"
#include "Tools.h"

void ObjectManager::ObjectListInit()
{
	ObjectList[Log]=			new Item(Log,	Recipe());
	ObjectList[Plank]=			new Item(Plank,	Recipe(Plank, Smithing,1.0f, Log, 1));
	ObjectList[Stick]=			new Item(Stick,	Recipe(Stick, Smithing,1.0f, Log, 2));
	ObjectList[Stone]=			new Item(Stone,	Recipe());
	ObjectList[Brick]=			new Item(Brick,	Recipe(Brick, Smithing, 1.0f, Stone, 1));
	ObjectList[GoldenCoin]=		new Item(GoldenCoin, Recipe());		  

	ObjectList[CopperOre]=		new Item(CopperOre,		Recipe());
	ObjectList[IronOre]=		new Item(IronOre,		Recipe());
	ObjectList[Coal]=			new Item(Coal,			Recipe(Coal, Smithing,1.0f,Log,2));
	ObjectList[MithrilOre]=		new Item(MithrilOre,	Recipe());
	ObjectList[OrichalcumOre]=	new Item(OrichalcumOre,	Recipe());
	ObjectList[AdamantOre]=		new Item(AdamantOre,	Recipe());
	ObjectList[PromethiumOre]=	new Item(PromethiumOre,	Recipe());

	ObjectList[CopperBar]=		new Item(CopperBar,		Recipe(CopperBar,	  Smithing, 3.0f, CopperOre, 2, Coal, 1));
	ObjectList[IronBar]=		new Item(IronBar,		Recipe(IronBar,		  Smithing, 3.0f, IronOre, 2, Coal, 1));
	ObjectList[SteelBar]=		new Item(SteelBar,		Recipe(SteelBar,	  Smithing, 3.0f, IronOre, 3, Coal, 2));
	ObjectList[MithrilBar]=		new Item(MithrilBar,	Recipe(MithrilBar,	  Smithing, 3.0f, MithrilOre, 2, Coal, 1));
	ObjectList[OrichalcumBar]=	new Item(OrichalcumBar,	Recipe(OrichalcumBar, Smithing, 3.0f, OrichalcumOre, 2, Coal, 1));
	ObjectList[AdamantBar]=		new Item(AdamantBar,	Recipe(AdamantBar,	  Smithing, 3.0f, AdamantOre, 2, Coal, 1));
	ObjectList[PromethiumBar]=	new Item(PromethiumBar,	Recipe(PromethiumBar, Smithing, 3.0f, PromethiumOre, 2, Coal, 1));

	ObjectList[RawMeat]=		new Food(RawMeat,	 5, Recipe());
	ObjectList[CookedMeat]=		new Food(CookedMeat, 15, Recipe(CookedMeat,Cooking, 3.0f, RawMeat, 1, Coal, 1));
	ObjectList[Apple]=			new Food(Apple,		 1, Recipe());
	ObjectList[Wheat]=			new Food(Wheat,		 1, Recipe());
	ObjectList[Potato]=			new Food(Potato,	 1, Recipe());
	ObjectList[Beans]=			new Food(Beans,		 1, Recipe());

	ObjectList[Wolfsbane]=		new Plant(Wolfsbane);
	ObjectList[Dandelion]=		new Plant(Dandelion);
	ObjectList[Marigold]=		new Plant(Marigold);
	ObjectList[Rosemary]=		new Plant(Rosemary); 
	ObjectList[Mushroom]=		new Plant(Mushroom);
	ObjectList[Feybell]=		new Plant(Feybell);
	ObjectList[Deeproot]=		new Plant(Deeproot); 
	ObjectList[Clover]=			new Plant(Clover);

#pragma region Tools
#pragma region Wooden
	ObjectList[WoodenShield]=	new Armory(WoodenShield,	1,	Head,			Recipe(WoodenShield,	Smithing, 2.0f, Plank, 4, Stick, 1));
	ObjectList[WoodenSword]=	new Tools(WoodenSword,		2,  Sword,	Wooden, Recipe(WoodenSword,		Smithing, 2.0f, Plank, 3, Stick, 1));
	ObjectList[WoodenBow]=		new Tools(WoodenBow,		10, Bow,	Wooden, Recipe(WoodenBow,		Smithing, 2.0f, Plank, 2, Stick, 1));
	ObjectList[WoodenArrow]=	new Tools(WoodenArrow,		10, Arrow,	Wooden, Recipe(WoodenArrow,		Smithing, 2.0f, Plank, 2, Stick, 1));
	ObjectList[WoodenAxe]=		new Tools(WoodenAxe,		10, Axe,	Wooden, Recipe(WoodenAxe,		Smithing, 2.0f, Plank, 1, Stick, 1));
	ObjectList[WoodenPickaxe]=	new Tools(WoodenPickaxe,	10, Pickaxe,Wooden, Recipe(WoodenPickaxe,	Smithing, 2.0f, Plank, 2, Stick, 1));
	ObjectList[WoodenHoe]=		new Tools(WoodenHoe,		10, Hoe,	Wooden,	Recipe(WoodenHoe,		Smithing, 2.0f, Plank, 2, Stick, 1));
	ObjectList[WoodenHammer]=	new Tools(WoodenHammer,		10, Hammer,	Wooden,	Recipe(WoodenHammer,	Smithing, 2.0f, Plank, 2, Stick, 1));
#pragma endregion
#pragma region Stone
	ObjectList[StoneShield]=	new Armory(StoneShield,		2,	Head,			Recipe(StoneShield,	Smithing, 2.0f, Stone, 4, Stick, 1));
	ObjectList[StoneSword]=		new Tools(StoneSword,		3,  Bow,	StoneT,	Recipe(StoneSword,	Smithing, 2.0f, Stone, 3, Stick, 1));
	ObjectList[StoneArrow]=		new Tools(StoneArrow,		10, Arrow,	StoneT,	Recipe(StoneArrow,	Smithing, 2.0f, Stone, 2, Stick, 1));
	ObjectList[StoneAxe]=		new Tools(StoneAxe,			10, Axe,	StoneT,	Recipe(StoneAxe,	Smithing, 2.0f, Stone, 1, Stick, 1));
	ObjectList[StonePickaxe]=	new Tools(StonePickaxe,		10, Pickaxe,StoneT,	Recipe(StonePickaxe,Smithing, 2.0f, Stone, 2, Stick, 1));
	ObjectList[StoneHoe]=		new Tools(StoneHoe,			10, Hoe,	StoneT,	Recipe(StoneHoe,	Smithing, 2.0f, Stone, 2, Stick, 1));
	ObjectList[StoneHammer]=	new Tools(StoneHammer,		10, Hammer,	StoneT,	Recipe(StoneHammer,	Smithing, 2.0f, Stone, 2, Stick, 1));
#pragma endregion											
#pragma region Copper
	ObjectList[CopperShield]=	new Armory(CopperShield,	3,	Head,			Recipe(CopperShield,	Smithing, 2.0f, CopperBar, 4, Stick, 1));
	ObjectList[CopperSword]=	new Tools(CopperSword,		4,  Bow,	Copper,	Recipe(CopperSword,		Smithing, 2.0f, CopperBar, 3, Stick, 1));
	ObjectList[CopperArrow]=	new Tools(CopperArrow,		10, Arrow,	Copper,	Recipe(CopperArrow,		Smithing, 2.0f, CopperBar, 2, Stick, 1));
	ObjectList[CopperAxe]=		new Tools(CopperAxe,		10, Axe,	Copper,	Recipe(CopperAxe,		Smithing, 2.0f, CopperBar, 1, Stick, 1));
	ObjectList[CopperPickaxe]=	new Tools(CopperPickaxe,	10, Pickaxe,Copper,	Recipe(CopperPickaxe,	Smithing, 2.0f, CopperBar, 2, Stick, 1));
	ObjectList[CopperHoe]=		new Tools(CopperHoe,		10, Hoe,	Copper,	Recipe(CopperHoe,		Smithing, 2.0f, CopperBar, 2, Stick, 1));
	ObjectList[CopperHammer]=	new Tools(CopperHammer,		10, Hammer,	Copper,	Recipe(CopperHammer,	Smithing, 2.0f, CopperBar, 2, Stick, 1));
#pragma endregion
#pragma region Iron
	ObjectList[IronShield]=		new Armory(IronShield,		4,	Head,			Recipe(IronShield,	Smithing, 2.0f, IronBar, 4, Stick, 1));
	ObjectList[IronSword]=		new Tools(IronSword,		5,  Bow,	Iron,	Recipe(IronSword,	Smithing, 2.0f, IronBar, 3, Stick, 1));
	ObjectList[IronArrow]=		new Tools(IronArrow,		10, Arrow,	Iron,	Recipe(IronArrow,	Smithing, 2.0f, IronBar, 2, Stick, 1));
	ObjectList[IronAxe]=		new Tools(IronAxe,			10, Axe,	Iron,	Recipe(IronAxe,		Smithing, 2.0f, IronBar, 1, Stick, 1));
	ObjectList[IronPickaxe]=	new Tools(IronPickaxe,		10, Pickaxe,Iron,	Recipe(IronPickaxe,	Smithing, 2.0f, IronBar, 2, Stick, 1));
	ObjectList[IronHoe]=		new Tools(IronHoe,			10, Hoe,	Iron,	Recipe(IronHoe,		Smithing, 2.0f, IronBar, 2, Stick, 1));
	ObjectList[IronHammer]=		new Tools(IronHammer,		10, Hammer,	Iron,	Recipe(IronHammer,	Smithing, 2.0f, IronBar, 2, Stick, 1));
#pragma endregion
#pragma region Steel
	ObjectList[SteelShield]=	new Armory(SteelShield,		5,	Head,			Recipe(SteelShield,	Smithing, 2.0f, SteelBar, 4, Stick, 1));
	ObjectList[SteelSword]=		new Tools(SteelSword,		6,  Bow,	Steel,	Recipe(SteelSword,	Smithing, 2.0f, SteelBar, 3, Stick, 1));
	ObjectList[SteelArrow]=		new Tools(SteelArrow,		10, Arrow,	Steel,	Recipe(SteelArrow,	Smithing, 2.0f, SteelBar, 2, Stick, 1));
	ObjectList[SteelAxe]=		new Tools(SteelAxe,			10, Axe,	Steel,	Recipe(SteelAxe,	Smithing, 2.0f, SteelBar, 1, Stick, 1));
	ObjectList[SteelPickaxe]=	new Tools(SteelPickaxe,		10, Pickaxe,Steel,	Recipe(SteelPickaxe,Smithing, 2.0f, SteelBar, 2, Stick, 1));
	ObjectList[SteelHoe]=		new Tools(SteelHoe,			10, Hoe,	Steel,	Recipe(SteelHoe,	Smithing, 2.0f, SteelBar, 2, Stick, 1));
	ObjectList[SteelHammer]=	new Tools(SteelHammer,		10, Hammer,	Steel,	Recipe(SteelHammer,	Smithing, 2.0f, SteelBar, 2, Stick, 1));
#pragma endregion
#pragma region Mithril
	ObjectList[MithrilShield]=	new Armory(MithrilShield,	6,	Head,					Recipe(MithrilShield,	Smithing, 2.0f, MithrilBar, 4, Stick, 1));
	ObjectList[MithrilSword]=	new Tools(MithrilSword,		7,  Bow,		Mithril,	Recipe(MithrilSword,	Smithing, 2.0f, MithrilBar, 3, Stick, 1));
	ObjectList[MithrilArrow]=	new Tools(MithrilArrow,		10, Arrow,		Mithril,	Recipe(MithrilArrow,	Smithing, 2.0f, MithrilBar, 2, Stick, 1));
	ObjectList[MithrilAxe]=		new Tools(MithrilAxe,		10, Axe,		Mithril,	Recipe(MithrilAxe,		Smithing, 2.0f, MithrilBar, 1, Stick, 1));
	ObjectList[MithrilPickaxe]=	new Tools(MithrilPickaxe,	10, Pickaxe,	Mithril,	Recipe(MithrilPickaxe,	Smithing, 2.0f, MithrilBar, 2, Stick, 1));
	ObjectList[MithrilHoe]=		new Tools(MithrilHoe,		10, Hoe,		Mithril,	Recipe(MithrilHoe,		Smithing, 2.0f, MithrilBar, 2, Stick, 1));
	ObjectList[MithrilHammer]=	new Tools(MithrilHammer,	10, Hammer,		Mithril,	Recipe(MithrilHammer,	Smithing, 2.0f, MithrilBar, 2, Stick, 1));
#pragma endregion
#pragma region Orichalcum
	ObjectList[OrichalcumShield]=	new Armory(OrichalcumShield,7,	Head,				Recipe(OrichalcumShield,	Smithing, 2.0f, OrichalcumBar, 4, Stick, 1));
	ObjectList[OrichalcumSword]=	new Tools(OrichalcumSword,	8,  Bow,	Orichalcum,	Recipe(OrichalcumSword,		Smithing, 2.0f, OrichalcumBar, 3, Stick, 1));
	ObjectList[OrichalcumArrow]=	new Tools(OrichalcumArrow,	10, Arrow,	Orichalcum,	Recipe(OrichalcumArrow,		Smithing, 2.0f, OrichalcumBar, 2, Stick, 1));
	ObjectList[OrichalcumAxe]=		new Tools(OrichalcumAxe,	10, Axe,	Orichalcum,	Recipe(OrichalcumAxe,		Smithing, 2.0f, OrichalcumBar, 1, Stick, 1));
	ObjectList[OrichalcumPickaxe]=	new Tools(OrichalcumPickaxe,10, Pickaxe,Orichalcum,	Recipe(OrichalcumPickaxe,	Smithing, 2.0f, OrichalcumBar, 2, Stick, 1));
	ObjectList[OrichalcumHoe]=		new Tools(OrichalcumHoe,	10, Hoe,	Orichalcum,	Recipe(OrichalcumHoe,		Smithing, 2.0f, OrichalcumBar, 2, Stick, 1));
	ObjectList[OrichalcumHammer]=	new Tools(OrichalcumHammer,	10, Hammer,	Orichalcum,	Recipe(OrichalcumHammer,	Smithing, 2.0f, OrichalcumBar, 2, Stick, 1));
#pragma endregion
#pragma region Adamant
	ObjectList[AdamantShield]=	new Armory(AdamantShield,	8,	Head,				Recipe(AdamantShield,	Smithing, 2.0f, AdamantBar, 4, Stick, 1));
	ObjectList[AdamantSword]=	new Tools(AdamantSword,		9,  Bow,	Adamant,	Recipe(AdamantSword,	Smithing, 2.0f, AdamantBar, 3, Stick, 1));
	ObjectList[AdamantArrow]=	new Tools(AdamantArrow,		10, Arrow,	Adamant,	Recipe(AdamantArrow,	Smithing, 2.0f, AdamantBar, 2, Stick, 1));
	ObjectList[AdamantAxe]=		new Tools(AdamantAxe,		10, Axe,	Adamant,	Recipe(AdamantAxe,		Smithing, 2.0f, AdamantBar, 1, Stick, 1));
	ObjectList[AdamantPickaxe]=	new Tools(AdamantPickaxe,	10, Pickaxe,Adamant,	Recipe(AdamantPickaxe,	Smithing, 2.0f, AdamantBar, 2, Stick, 1));
	ObjectList[AdamantHoe]=		new Tools(AdamantHoe,		10, Hoe,	Adamant,	Recipe(AdamantHoe,		Smithing, 2.0f, AdamantBar, 2, Stick, 1));
	ObjectList[AdamantHammer]=	new Tools(AdamantHammer,	10, Hammer,	Adamant,	Recipe(AdamantHammer,	Smithing, 2.0f, AdamantBar, 2, Stick, 1));
#pragma endregion
#pragma region Promethium
	ObjectList[PromethiumShield]=	new Armory(PromethiumShield,9,	Head,				Recipe(PromethiumShield,	Smithing, 2.0f, PromethiumBar, 4, Stick, 1));
	ObjectList[PromethiumSword]=	new Tools(PromethiumSword,	10, Bow,	Promethium,	Recipe(PromethiumSword,		Smithing, 2.0f, PromethiumBar, 3, Stick, 1));
	ObjectList[PromethiumArrow]=	new Tools(PromethiumArrow,	10, Arrow,	Promethium,	Recipe(PromethiumArrow,		Smithing, 2.0f, PromethiumBar, 2, Stick, 1));
	ObjectList[PromethiumAxe]=		new Tools(PromethiumAxe,	10, Axe,	Promethium,	Recipe(PromethiumAxe,		Smithing, 2.0f, PromethiumBar, 1, Stick, 1));
	ObjectList[PromethiumPickaxe]=	new Tools(PromethiumPickaxe,10, Pickaxe,Promethium,	Recipe(PromethiumPickaxe,	Smithing, 2.0f, PromethiumBar, 2, Stick, 1));
	ObjectList[PromethiumHoe]=		new Tools(PromethiumHoe,	10, Hoe,	Promethium,	Recipe(PromethiumHoe,		Smithing, 2.0f, PromethiumBar, 2, Stick, 1));
	ObjectList[PromethiumHammer]=	new Tools(PromethiumHammer,	10, Hammer,	Promethium,	Recipe(PromethiumHammer,	Smithing, 2.0f, PromethiumBar, 2, Stick, 1));
#pragma endregion
#pragma endregion
	ObjectList[FTree]=				new CTree(FTree);
	ObjectList[PTree]=				new CTree(PTree);
	ObjectList[PSTree]=				new CTree(PSTree);
	ObjectList[WheatFarm]=			new Farmland(WheatFarm);
	ObjectList[PotatoFarm]=			new Farmland(PotatoFarm);
	ObjectList[BeansFarm]=			new Farmland(BeansFarm);

	ObjectList[AlchemyTable]=		new Building(AlchemyTable, _btAlchemyTable,Recipe(AlchemyTable,Construction,3.0f,Log,2,Stone,2));
	ObjectList[Forge]=				new Building(Forge, _btForge,Recipe(Forge, Construction, 3.0f,Stone,10));
	ObjectList[Kitchen]=			new Building(Kitchen, _btKitchen,Recipe(Kitchen, Construction, 3.0f, Log, 1, Stone, 1));
	ObjectList[WorkBench]=			new Building(WorkBench, _btWorkBench,Recipe(WorkBench,Construction,3.0f,Log,1));
	ObjectList[_ConstructionLand]=	new ConstructionLand(_ConstructionLand);
	ObjectList[lvDoor]=				new LvDoor();

	ObjectList[PortalKey]=			new Key();
	//Farmland
	//Obstacle
	ObjectList[MRStone]=		new MiningRocks(MRStone,		_mtStone);
	ObjectList[MRCopper]=		new MiningRocks(MRCopper,		_mtCopper);
	ObjectList[MRIron]=			new MiningRocks(MRIron,			_mtIron);
	ObjectList[MRCoal]=			new MiningRocks(MRCoal,			_mtCoal);
	ObjectList[MRMithril]=		new MiningRocks(MRMithril,		_mtMithril);
	ObjectList[MROrichalcum]=	new MiningRocks(MROrichalcum,	_mtOrichalcum);
	ObjectList[MRAdamant]=		new MiningRocks(MRAdamant,		_mtAdamant);
	ObjectList[MRPromethium]=	new MiningRocks(MRPromethium,	_mtPromethium);
	ObjectList[Wall]=			new MiningRocks(Wall,			_mtStone);


	ObjectList[Chest]=			new Chests(Chest, Recipe(Chest, Construction ,5.0f,Plank,6));

	ObjectList[_Colonist]=		new Colonist(_Colonist);

	//Potion
	ObjectList[AttackPotion]=		new Potion(AttackPotion,P_Attack,1,Recipe(AttackPotion, Alchemy,10.0f,RawMeat,1,Wolfsbane,1));
	ObjectList[SpeedPotion]=		new Potion(SpeedPotion,P_Speed,1,Recipe(SpeedPotion, Alchemy,10.0f,Dandelion,1,Beans,1));
	ObjectList[HealingPotion]=		new Potion(HealingPotion,P_Healing,1,Recipe(HealingPotion, Alchemy,10.0f,Marigold,1, Apple,1));
	ObjectList[DefensePotion]=		new Potion(DefensePotion,P_Defense,1,Recipe(DefensePotion, Alchemy,10.0f,Rosemary,1,Potato,1));
	ObjectList[IntelligencePotion]=	new Potion(IntelligencePotion,P_Intelligence,1,Recipe(IntelligencePotion, Alchemy,10.0f,Feybell,1,Mushroom,1));
	ObjectList[CarryingPotion]=		new Potion(CarryingPotion,P_Carrying,1,Recipe(CarryingPotion, Alchemy,10.0f,Deeproot,1,Wheat,1));
	ObjectList[LuckPotion]=			new Potion(LuckPotion,P_Luck,1,Recipe(LuckPotion, Alchemy,10.0f,Clover,1,GoldenCoin,1));

#pragma region Enemy
	//Health, Damage, Armor
	ObjectList[Slime]=			new Enemy(Slime, 3,3,3);
	ObjectList[Wolf]=			new Enemy(Wolf, 3,3,3);
	ObjectList[Skeleton]=		new Enemy(Skeleton, 8,2,0);
#pragma endregion  
	ObjectList[Cow]=			new Animal(Cow);
	ObjectList[Chicken]=		new Animal(Chicken);
	ObjectList[Pig]=			new Animal(Pig);


	std::unordered_map<Object_List, Object*>::iterator it = ObjectList.begin();
	while (it !=ObjectList.end())
	{
		it->second->SetLevelManager(LM);
		it->second->SetObjectManager(this);
		it++;
	}
}

Object * ObjectManager::CheckTile(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count)
{
	Object* result = nullptr;
	Object* temp = nullptr;
	bool IsIm = dynamic_cast<ImmobileObject*>(GetObj(item));
	if (IsIm)
		temp = LM->GetTileMap()->GetTile(y, x, z)->GetImmobileObject();
	else 
		temp = LM->GetTileMap()->GetTile(y, x, z)->GetMobileObject();

	if (temp)
	{
		if (temp->GetObjectType() == item)
		{
			temp->SetJob(Jobs::Pickup);
			result = temp;
		}
	}
	return result;
}

Object * ObjectManager::CheckTile2(unsigned int x, unsigned int y, unsigned int z, Object_List item)
{
	Object* result = nullptr;
	Object* temp = nullptr;
	bool IsIm = dynamic_cast<ImmobileObject*>(GetObj(item));
	if (IsIm)
		temp = LM->GetTileMap()->GetTile(y, x, z)->GetImmobileObject();
	else 
		temp = LM->GetTileMap()->GetTile(y, x, z)->GetMobileObject();

	if (temp)
	{
		if (temp->GetObjectType() == item && !temp->FgLooking)
		{
			temp->FgLooking = true;
			result = temp;
		}
	}
	return result;
}

ObjectManager::ObjectManager()
{

}

ObjectManager::~ObjectManager()
{

}

void ObjectManager::Initial(GraphicsManager* gm, AI* aim, LevelManager* lm)
{
	GM = gm;
	AIM = aim;
	LM = lm;
	GM->AddEmitter(XMMatrixIdentity(), -1, EXPLOSION_SPRITE, true);
	GM->AddEmitter(XMMatrixIdentity(), -1, BLOOD_SPRITE, true);
	GM->AddEmitter(XMMatrixIdentity(), -1, SPARKLE_SPRITE, true, XMFLOAT4(0, 0, 0, 0), XMFLOAT4(.64705f, .16740f, .16740f, 1.0f)); //2, brown
	GM->AddEmitter(XMMatrixIdentity(), -1, SPARKLE_SPRITE, true, XMFLOAT4(0, 0, 0, 0), XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f)); //3, yellow
	GM->AddEmitter(XMMatrixIdentity(), -1, SPARKLE_SPRITE, true, XMFLOAT4(0, 0, 0, 0), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)); //4, green
	GM->AddEmitter(XMMatrixIdentity(), -1, SPARKLE_SPRITE, true, XMFLOAT4(0, 0, 0, 0), XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f)); //5, gray
	GM->AddEmitter(XMMatrixIdentity(), -1, SPARKLE_SPRITE, true, XMFLOAT4(0, 0, 0, 0), XMFLOAT4(0.82745f, 0.82745f, 0.82745f, 1.0f)); //6, light gray

	ObjectListInit();
}

void ObjectManager::EndGame()
{
	for (size_t ot = 0; ot < _otMAX; ot++)
	{
		for (size_t i = 0; i < LiveObjectList[ot].size(); i++)
		{
			if (LiveObjectList[ot][i] != nullptr)
			{
				Object* temp = LiveObjectList[ot][i];
				delete temp;
				LiveObjectList[ot][i] = nullptr;
			}
		}
		LiveObjectList[ot].clear();
	}
	for (size_t i = 0; i < LiveRequestList.size(); i++)
	{
		if (LiveRequestList[i] != nullptr)
		{
			Object* temp = LiveRequestList[i];
			delete temp;
			LiveRequestList[i] = nullptr;
		}
	}
	for (size_t i = 0; i < _MaxJobs; i++)
	{
		JobList[i].clear();
	}
	LiveRequestList.clear();
}

void ObjectManager::NewGame()
{
}

bool ObjectManager::Destroy(Object* object)
{
	for (size_t j = 0; j < _otMAX; j++)
	{
		for (size_t i = 0; i < LiveObjectList[j].size(); i++)
		{
			if (LiveObjectList[j][i] == object)
			{
				if (dynamic_cast<ImmobileObject*>(object))
				{
					if (LM->GetTileMap()->GetTile(object->Pos_n_Matrix.Pos.Y, object->Pos_n_Matrix.Pos.X, object->Pos_n_Matrix.Pos.Z)->GetImmobileObject() == object)
						LM->GetTileMap()->GetTile(object->Pos_n_Matrix.Pos.Y, object->Pos_n_Matrix.Pos.X, object->Pos_n_Matrix.Pos.Z)->SetImmobileObject(nullptr);
				}
				else if (dynamic_cast<MobileObject*>(object))
				{
					if (LM->GetTileMap()->GetTile(object->Pos_n_Matrix.Pos.Y, object->Pos_n_Matrix.Pos.X, object->Pos_n_Matrix.Pos.Z)->GetMobileObject() == object)
						LM->GetTileMap()->GetTile(object->Pos_n_Matrix.Pos.Y, object->Pos_n_Matrix.Pos.X, object->Pos_n_Matrix.Pos.Z)->SetMobileObject(nullptr);
				}
				object->Visible = false;
				Trash.push_back(object);
				LiveObjectList[j].erase(LiveObjectList[j].begin() + i);
				Jobs job = object->GetJob();
				ObjectCounter[object->GetObjectType()]--;
				for (size_t in = 0; in < JobList[job].size(); in++)
				{
					if (JobList[job][in] == object)
					{
						JobList[job].erase(JobList[job].begin() + in);
						break;
					}
				}
				return true;
			}
		}
	}
	return false;
}

void ObjectManager::Shutdown()
{
	EndGame();
	std::unordered_map<Object_List, Object*>::iterator it = ObjectList.begin();
	while (it !=ObjectList.end())
	{
		delete it->second;
		it++;
	}
}

void ObjectManager::Update(float Dtime)
{
	for (size_t ot = 0; ot < _otMAX; ot++)
	{
		for (size_t i = 0; i < LiveObjectList[ot].size(); i++)
		{
			LiveObjectList[ot][i]->Update(Dtime);
		}
	}
	while (Trash.size()!=0)
	{
		Object* temp = Trash[0];
		Trash.erase(Trash.begin());
		delete temp;
	}
}

Object * ObjectManager::Create(Object_List Type, XMMATRIX Matrix, int x, int y, int z)
{
	Object* temp =nullptr;
	Object::Position_and_Matrix pos;
	pos.Matrix = Matrix;
	pos.Offset = { 0,0 };
	pos.Pos.X = x;pos.Pos.Y = y;pos.Pos.Z = z;
	if (Type > _MobileObject)
	{
		if (Type>_Animal) //Animal
		{
			Animal* temp2 = new Animal(*dynamic_cast<Animal*>(ObjectList[Type]));
			temp2->SetAIManager(AIM);
			temp2->SetLevelManager(LM);
			temp2->SetObjectManager(this);
			temp = temp2;
			if (temp != nullptr) LiveObjectList[_otAnimals].push_back(temp);
		}
		else if (Type > _Enemy) //Enemy
		{
			//if (Type == Skeleton)
			//{
			//	Enemy* temp2 = new Enemy(Skeleton);
			//	temp2->SetAIManager(AIM);
			//	temp2->SetStartPosition(x, y, z);
			//	temp2->SetLevelManager(LM);
			//	temp2->SetObjectManager(this);
			//	temp = temp2;
			//	if (temp != nullptr) LiveObjectList[_otEnemies].push_back(temp);
			//}
			/*else*/
			{
				temp = new Enemy(*dynamic_cast<Enemy*>(ObjectList[Type]));
				if (temp != nullptr)
				{
					((Enemy*)temp)->SetAIManager(AIM);
					((Enemy*)temp)->SetStartPosition(x, y, z);
					((Enemy*)temp)->SetLevelManager(LM);
					((Enemy*)temp)->SetObjectManager(this);
					LiveObjectList[_otEnemies].push_back(temp);
				}
			}
		}
		else  //Colonist
		{
			if (Type == _Colonist)
			{
				Colonist* temp2 = new Colonist(*dynamic_cast<Colonist*>(ObjectList[Type]));
				temp2->SetAIManager(AIM);
				temp = temp2;
				if (temp != nullptr) LiveObjectList[_otColonist].push_back(temp);
			}
		}
	}
	else  //Immobile
	{
		if (Type > _Buildings)
		{
			if (Type == Chest)
			{
				temp = new Chests(*dynamic_cast<Chests*>(ObjectList[Type]),pos);
				if (temp != nullptr) LiveObjectList[_otChest].push_back(temp);
			}
			else if (Type == PortalKey)
			{
				temp = new Key(*dynamic_cast<Key*>(ObjectList[Type]));
				if (temp != nullptr) LiveObjectList[_otDoors].push_back(temp);
			}
			else if (Type == _ConstructionLand)
			{
				temp = new ConstructionLand(*dynamic_cast<ConstructionLand*>(ObjectList[Type]),pos);
				if (temp != nullptr) LiveObjectList[_otBuildings].push_back(temp);
			}
			else if (Type == lvDoor)
			{
				temp = new LvDoor(pos);
				if (temp != nullptr) LiveObjectList[_otDoors].push_back(temp);
			}
			else
			{
				temp = new Building(*dynamic_cast<Building*>(ObjectList[Type]));
				if (temp != nullptr) LiveObjectList[_otBuildings].push_back(temp);
			}
		}
		else if (Type> _Sources)
		{
			if (Type > _MiningRock)
			{
				if (Type == Wall)
				{
					temp = new MiningRocks(*dynamic_cast<MiningRocks*>(ObjectList[Type]));
					if (temp != nullptr) LiveObjectList[_otWalls].push_back(temp);
				}
				else
				{
					temp = new MiningRocks(*dynamic_cast<MiningRocks*>(ObjectList[Type]));
					if (temp != nullptr) LiveObjectList[_otSources].push_back(temp);
				}
			}
			else
			{
				if (Type == FTree||Type == PTree||Type ==PSTree)
				{
					temp = new CTree(Type, pos);
					if (temp != nullptr) LiveObjectList[_otSources].push_back(temp);
				}
				else
				{
					temp = new Farmland(*dynamic_cast<Farmland*>(ObjectList[Type]));
					if (temp != nullptr) LiveObjectList[_otSources].push_back(temp);
				}
			}
		}
		else if (Type > _Armory)
		{
			temp = new Armory(*dynamic_cast<Armory*>(ObjectList[Type]));
			if (temp != nullptr) LiveObjectList[_otItems].push_back(temp);
		}
		else if (Type > _Tool)
		{
			temp = new Tools(*dynamic_cast<Tools*>(ObjectList[Type]));
			if (temp != nullptr) LiveObjectList[_otItems].push_back(temp);
		}
		else if (Type > _Food) //Food
		{
			temp = new Food(*dynamic_cast<Food*>(ObjectList[Type]));
			if (temp != nullptr) LiveObjectList[_otResources].push_back(temp);
		}
		else if (Type > _Resources)
		{
			if (Type > GoldenCoin)
			{
				temp = new Plant(*dynamic_cast<Plant*>(ObjectList[Type]));
				if (temp != nullptr) LiveObjectList[_otResources].push_back(temp);
			}
			else
			{
				temp = new Item(*dynamic_cast<Item*>(ObjectList[Type]));
				if (temp != nullptr) LiveObjectList[_otResources].push_back(temp);
			}
		}
		else
		{

		}
	}
	if (temp == nullptr)
		return temp;
	temp->Pos_n_Matrix.Matrix = Matrix;
	temp->Pos_n_Matrix.Pos.X = x;
	temp->Pos_n_Matrix.Pos.Y = y;
	temp->Pos_n_Matrix.Pos.Z = z;
	temp->SetLevelManager(LM);
	temp->SetObjectManager(this);
	JobList[temp->GetJob()].push_back(temp);
	ObjectCounter[Type]++;
	return temp;
}

Object * ObjectManager::Create(Object * object)
{
	return Create(
		object->GetObjectType(),
		object->Pos_n_Matrix.Matrix,
		object->Pos_n_Matrix.Pos.X,
		object->Pos_n_Matrix.Pos.Y,
		object->Pos_n_Matrix.Pos.Z);
}
Object * ObjectManager::Create(Object * object,Object::Position_and_Matrix pnm )
{
	return Create(
		object->GetObjectType(),
		pnm.Matrix,
		pnm.Pos.X,
		pnm.Pos.Y,
		pnm.Pos.Z);
}

void ObjectManager::ApplyJob(Object * object, Jobs job)
{
	if (object != nullptr)
	{
		Jobs oldjob = object->GetJob();
		for (size_t i = 0; i < JobList[oldjob].size(); i++)
		{
			if (JobList[oldjob][i] == object)
			{
				JobList[oldjob].erase(JobList[oldjob].begin() + i);
				break;
			}
		}

		object->SetDeltaTime(0);
		JobList[job].push_back(object);
	}
}

Object * ObjectManager::FindJob(Jobs looking, Colonist* col)
{
	Object* thejob = nullptr;
	int dis = INT32_MAX;
	for (size_t i = 0; i < JobList[looking].size(); i++)
	{
		int distance = std::abs(JobList[looking][i]->Pos_n_Matrix.Pos.X - col->PosX)
			+ std::abs(JobList[looking][i]->Pos_n_Matrix.Pos.Z - col->PosZ)
			+ std::abs(JobList[looking][i]->Pos_n_Matrix.Pos.Y - col->PosY) * 6000;
		if (distance < dis && !JobList[looking][i]->GetJobClaim())
		{
			if (looking == Mining)
			{
				if (col->GetMining_gear())
				{
					if (col->GetMining_gear()->GetMakeType() + 2 > ((MiningRocks*)JobList[looking][i])->GetRockType())
					{
						dis = distance;
						thejob = JobList[looking][i];
					}
				}
			}
			else
			{
				dis = distance;
				thejob = JobList[looking][i];
			}
		}
	}
	return thejob;
}

Colonist * ObjectManager::FindColonist(unsigned int x, unsigned int y, unsigned int z)
{
	Colonist* temp = nullptr;
	int dis = INT32_MAX;
	for (size_t i = 0; i < LiveObjectList[_otColonist].size(); i++)
	{
		int distance = std::abs(LiveObjectList[_otColonist][i]->Pos_n_Matrix.Pos.X - (int)x)
			+ std::abs(LiveObjectList[_otColonist][i]->Pos_n_Matrix.Pos.Z - (int)z)
			+ std::abs(LiveObjectList[_otColonist][i]->Pos_n_Matrix.Pos.Y - (int)y) * 6000;
		if (distance < dis)
		{
			dis = distance;
			temp = (Colonist*)LiveObjectList[_otColonist][i];
		}
	}
	return temp;
}
Animal* ObjectManager::FindAnimal(unsigned int x, unsigned int y, unsigned int z)
{
	Animal* temp = nullptr;
	int dis = INT32_MAX;
	for (size_t i = 0; i < LiveObjectList[_otAnimals].size(); i++)
	{
		int distance = std::abs(LiveObjectList[_otAnimals][i]->Pos_n_Matrix.Pos.X - (int)x)
			+ std::abs(LiveObjectList[_otAnimals][i]->Pos_n_Matrix.Pos.Z - (int)z)
			+ std::abs(LiveObjectList[_otAnimals][i]->Pos_n_Matrix.Pos.Y - (int)y) * 6000;
		if (distance < dis && LiveObjectList[_otAnimals][i]->GetJob()==Jobs::Hunting)
		{
			dis = distance;
			temp = (Animal*)LiveObjectList[_otAnimals][i];
		}
	}
	return temp;
}

Chests * ObjectManager::FindChest(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count)
{
	Chests* result = nullptr;
	Chests* temp = nullptr;
	int dis = INT32_MAX;
	for (size_t i = 0; i < LiveObjectList[_otChest].size(); i++)
	{
		int distance = std::abs(LiveObjectList[_otChest][i]->Pos_n_Matrix.Pos.X - (int)x)
			+ std::abs(LiveObjectList[_otChest][i]->Pos_n_Matrix.Pos.Z - (int)z)
			+ std::abs(LiveObjectList[_otChest][i]->Pos_n_Matrix.Pos.Y - (int)y) * 6000;
		temp = (Chests*)LiveObjectList[_otChest][i];
		if (temp->IfEnough(item,count) && distance < dis)
		{
			dis = distance;
			result = (Chests*)LiveObjectList[_otChest][i];
		}
	}
	return result;
}

Object * ObjectManager::FindObjectOntheGround(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count)
{
	Object* result = nullptr;
	Object* temp = nullptr;
	result = CheckTile(x, y, z, item, count);
	if (result) return result;

	int depth = 0; int xpos, xneg, zpos, zneg;
	while (depth<20)
	{
		depth++;
		xpos = x + depth; if (xpos > 127)	xpos = 127;
		xneg = x - depth; if (xneg < 0)		xneg = 0;
		zpos = z + depth; if (zpos > 127)	zpos = 127;
		zneg = z - depth; if (zneg < 0)		zneg = 0;
		for (size_t i = xneg; i < xpos+1; i++)
		{
			result = CheckTile((int)i, y, zpos, item, count);
			if (result) return result;
			result = CheckTile((int)i, y, zneg, item, count);
			if (result) return result;
		}
		for (size_t i = zneg+1; i < zpos; i++)
		{
			result = CheckTile(xpos, y, (int)i, item, count);
			if (result) return result;
			result = CheckTile(xneg, y, (int)i, item, count);
			if (result) return result;
		}
	}
	return result;
}

Object * ObjectManager::FindClosestObject(unsigned int x, unsigned int y, unsigned int z, Object_List item, int count)
{
	Object* result = nullptr;
	result = FindChest(x, y, z, item, count);
	if (!result) result = FindObjectOntheGround(x, y, z, item, count);
	return result;
}

Object * ObjectManager::FindLiveObject(unsigned int x, unsigned int y, unsigned int z, Object_List item)
{
	for (size_t i = 0; i < _otMAX; i++)
	{
		for (size_t j = 0; j < LiveObjectList[i].size(); j++)
		{
			if(LiveObjectList[i][j]->GetObjectType() == item)
				if (LiveObjectList[i][j]->Pos_n_Matrix.Pos.X == x &&
					LiveObjectList[i][j]->Pos_n_Matrix.Pos.Y == y &&
					LiveObjectList[i][j]->Pos_n_Matrix.Pos.Z == z)
					return LiveObjectList[i][j];
		}
	}
	return nullptr;
}

Object * ObjectManager::FindObjectOntheGround2(unsigned int x, unsigned int y, unsigned int z, Object_List item)
{
	Object* result = nullptr;
	Object* temp = nullptr;
	result = CheckTile2(x, y, z, item);
	if (result) return result;

	int depth = 0; int xpos, xneg, zpos, zneg;
	while (depth<20)
	{
		depth++;
		xpos = x + depth; if (xpos > 127)	xpos = 127;
		xneg = x - depth; if (xneg < 0)		xneg = 0;
		zpos = z + depth; if (zpos > 127)	zpos = 127;
		zneg = z - depth; if (zneg < 0)		zneg = 0;
		for (size_t i = xneg; i < xpos+1; i++)
		{
			result = CheckTile2((int)i, y, zpos, item);
			if (result) return result;				 
			result = CheckTile2((int)i, y, zneg, item);
			if (result) return result;				 
		}											 
		for (size_t i = zneg+1; i < zpos; i++)		 
		{											 
			result = CheckTile2(xpos, y, (int)i, item);
			if (result) return result;				 
			result = CheckTile2(xneg, y, (int)i, item);
			if (result) return result;
		}
	}
	return result;
}

Object * ObjectManager::FindClosestObject2(unsigned int x, unsigned int y, unsigned int z, Object_List item)
{
	Object* result = nullptr;
	result = FindChest2(x, y, z, item);
	//if (!result) result = FindObjectOntheGround2(x, y, z, item);
	//if (!result) result = FindColonistWithObject(x, y, z, item);
	return result;
}

Object * ObjectManager::FindChest2(unsigned int x, unsigned int y, unsigned int z, Object_List item)
{
	Object* result = nullptr;
	Chests* temp = nullptr;
	int dis = INT32_MAX;
	for (size_t i = 0; i < LiveObjectList[_otChest].size(); i++)
	{
		int distance = std::abs(LiveObjectList[_otChest][i]->Pos_n_Matrix.Pos.X - (int)x)
			+ std::abs(LiveObjectList[_otChest][i]->Pos_n_Matrix.Pos.Z - (int)z)
			+ std::abs(LiveObjectList[_otChest][i]->Pos_n_Matrix.Pos.Y - (int)y) * 6000;
		temp = (Chests*)LiveObjectList[_otChest][i];
		if (temp->IfEnough(item, 1) && distance < dis)
		{
			dis = distance;
			result = ((Chests*)LiveObjectList[_otChest][i])->SearchItem(item);
		}
	}
	return result;
}

Object * ObjectManager::FindColonistWithObject(unsigned int x, unsigned int y, unsigned int z, Object_List item)
{
	Object* result = nullptr;
	Colonist* temp = nullptr;
	int dis = INT32_MAX;
	for (size_t i = 0; i < LiveObjectList[_otColonist].size(); i++)
	{
		int distance = std::abs(LiveObjectList[_otColonist][i]->Pos_n_Matrix.Pos.X - (int)x)
			+ std::abs(LiveObjectList[_otColonist][i]->Pos_n_Matrix.Pos.Z - (int)z)
			+ std::abs(LiveObjectList[_otColonist][i]->Pos_n_Matrix.Pos.Y - (int)y) * 6000;
		temp = (Colonist*)LiveObjectList[_otColonist][i];
		if (temp->GetBackPack()->IfEnough(item, 1) && distance < dis)
		{
			dis = distance;
			result = ((Chests*)LiveObjectList[_otChest][i])->SearchItem(item);
		}
	}
	return result;
}

Object * ObjectManager::FindStaircase(Colonist * col, bool up)
{
	for (size_t i = 0; i < LiveObjectList[_otDoors].size(); i++)
	{
		if(!((LvDoor*)LiveObjectList[_otDoors][i])->IsLocked())
			if (LiveObjectList[_otDoors][i]->PosY == col->PosY)
				if(((LvDoor*)LiveObjectList[_otDoors][i])->GoingUP == up)
					return LiveObjectList[_otDoors][i];
	}
	return nullptr;
}

Request * ObjectManager::FindRequest(Colonist * col)
{
	Request* Request = nullptr;
	int dis = INT32_MAX;
	for (size_t i = 0; i < LiveRequestList.size(); i++)
	{
		if (LiveRequestList[i]->col == col)
		{
			int distance = std::abs(LiveRequestList[i]->Pos_n_Matrix.Pos.X - col->PosX)
				+ std::abs(LiveRequestList[i]->Pos_n_Matrix.Pos.Z - col->PosZ)
				+ std::abs(LiveRequestList[i]->Pos_n_Matrix.Pos.Y - col->PosY) * 6000;
			if (distance < dis)
			{
				dis = distance;
				Request = LiveRequestList[i];
			}
		}
	}
	return Request;
}

bool ObjectManager::InitRequest(Request * req, Object::Position_and_Matrix pos)
{
	Recipe recipe = req->recipe;
	vector<Object*> templist;
	for (size_t i = 0; i < recipe.Ingre_list.size(); i++)
	{
		for (size_t j = 0; j < recipe.Ingre_list[i].count; j++)
		{
			Object* tempObj = FindClosestObject2(pos.Pos.X, pos.Pos.Y, pos.Pos.Z, recipe.Ingre_list[i].Ingre);
			if (tempObj)
				templist.push_back(tempObj);
			else
				goto leave;
		}
	}
	for (size_t i = 0; i < templist.size(); i++)
	{
		templist[i]->FgPickup = true;
		Req_Job tempRJ;
		tempRJ.Count = 1;
		tempRJ.Pos = templist[i]->Pos_n_Matrix;
		tempRJ.type = templist[i]->GetObjectType();
		req->AddTodo(tempRJ);
	}
	return true;
leave:
	for (size_t i = 0; i < templist.size(); i++)
		templist[i]->FgLooking = false;
	return false;
}

bool ObjectManager::AddRequest(Request * recipe)
{
	if (recipe)
	{
		LiveRequestList.push_back(recipe);
	}
	else 
		return false;
	return true;
}

bool ObjectManager::RemoveRequest(Request * recipe)
{
	for (size_t i = 0; i < LiveRequestList.size(); i++)
	{
		if (LiveRequestList[i] == recipe)
		{
			Request* temp= LiveRequestList[i];
			LiveRequestList.erase(LiveRequestList.begin()+i);
			delete temp;
			return true;
		}
	}
	return false;
}

int ObjectManager::GetCurrentColonistCount()
{
	char res[27] = "Current Colonist Left : ";
	_itoa_s((int)LiveObjectList[_otColonist].size(), &res[24], 3, 10);
	GetGM()->AddText(res,1152 , 0);
	return (int)LiveObjectList[_otColonist].size(); 
}

int ObjectManager::GetCurrentEnemyCount()
{
	char res[25] = "Current Enemy Left : ";
	_itoa_s((int)LiveObjectList[_otEnemies].size(), &res[21], 4, 10);
	GetGM()->AddText(res,1152 , 20);
	return (int)LiveObjectList[_otEnemies].size(); 
}

void ObjectManager::Colonist_DeathInform(Colonist * col)
{
	for (size_t i = 0; i < LiveRequestList.size(); i++)
	{
		if (LiveRequestList[i]->col == col)
		{
			if (LiveRequestList[i]->Jobtype != GearUp)
			{
				//Thats mean col is dead and need someone to replace the position
				//Find someone to take the job
				LiveRequestList[i]->col = FindColonist(LiveRequestList[i]->building->PosX, LiveRequestList[i]->building->PosY, LiveRequestList[i]->building->PosZ);
			}
			else
			{
				RemoveRequest(LiveRequestList[i]);
			}
		}
	}
}

void ObjectManager::AddBackPacktoArray(Backpack * bp)
{
	LiveObjectList[_otChest].push_back(bp);
}

void ObjectManager::UpdateUnlockedLayer(int lv)
{
	Unlockedlv = lv;
	for (size_t i = 0; i < LiveObjectList[_otBuildings].size(); i++)
	{
		if (dynamic_cast<Building*>(LiveObjectList[_otBuildings][i]))
			((Building*)LiveObjectList[_otBuildings][i])->MenuUpdate(lv);
	}
}

void ObjectManager::UpdateDifficulty(float lv)
{
	Difficulty = lv;
	for (size_t i = 0; i < LiveObjectList[_otEnemies].size(); i++)
	{
		if (dynamic_cast<Enemy*>(LiveObjectList[_otEnemies][i]))
			((Enemy*)LiveObjectList[_otEnemies][i])->SetEnemyDifficulty(lv);
	}
}

unsigned int ObjectManager::GetObjectCount(Object_List type)
{
	unsigned int result = 0;
	for (size_t i = 0; i < LiveObjectList[_otChest].size(); i++)
	{
		if (dynamic_cast<Chests*>(LiveObjectList[_otChest][i]))
			result += dynamic_cast<Chests*>(LiveObjectList[_otChest][i])->GetBackpack().GetObjectCountInChest(type);
		else if (dynamic_cast<Backpack*>(LiveObjectList[_otChest][i]))
			result += dynamic_cast<Backpack*>(LiveObjectList[_otChest][i])->GetObjectCountInChest(type);
	}
	return result;
}

vector<Object*> ObjectManager::GetLiveColonistList()
{
	return LiveObjectList[_otColonist];
}

vector<ChestCon> ObjectManager::GetChestContent()
{
	int count[_Max] = { 0 };
	vector<ChestCon> result;
	for (size_t i = 0; i < LiveObjectList[_otChest].size(); i++)
	{
		vector<Item*> temp=((Chests*)LiveObjectList[_otChest][i])->GetBackpack().GetStorage();
		for (size_t j = 0; j < temp.size(); j++)
			count[temp[j]->GetObjectType()]++;
	}
	for (size_t i = 0; i < _Max; i++)
	{
		if (count[i] > 0)
		{
			ChestCon temp;
			temp.count = count[i];
			temp.type = (Object_List)i;
			result.push_back(temp);
		}
	}
	return result;
}
#pragma endregion

#pragma region Food.h
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

#pragma endregion

#pragma region Food.cpp
#include "stdafx.h"
#include "Food.h"
#include "Colonist.h"

Food::Food(Object_List type, int boost,Recipe one)
	: Item(type, one)
{
	Boost = boost;
	switch (type)
	{
	case Meats:
		break;
	case Apple:
		this->meshindex = APPLE_GROUP_INDEX;
		break;
	default:
		break;
	}
}

Food::Food(const Food & obj) : Item(obj)
{
	this->Boost = obj.Boost;
}

Food::~Food()
{
}

void Food::Eat(Colonist * col)
{
	col->Heal(this->Boost);
	OM->Destroy(this);
}

Object * Food::Interact(Jobs job, float Delta, Object * objinput, Object_List make, int count)
{
	Object* result = nullptr;
	if (GetJob() == job)
	{
		switch (job)
		{
		case Hauling:
		{
			this->Visible = false;
			if (LM->GetTileMap()->GetTile(this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Z)->GetImmobileObject() == this)
				LM->GetTileMap()->GetTile(this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Z)->SetImmobileObject(nullptr);
			SetJob(None);
			result = this;
			result->ItemState = InInven;
			result->SetJobClaim(nullptr);
			break;
		}
		case Consuming:
		{
			Eat((Colonist*)objinput);
			if (LM->GetTileMap()->GetTile(this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Z)->GetImmobileObject() == this)
				LM->GetTileMap()->GetTile(this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Z)->SetImmobileObject(nullptr);
			break;
		}
		default:
			DTime = 0;
			break;
		}
	}
	return result;
}

int Food::RCSetup(Functionptr * f,ActionBtn* btn)
{
	switch (ItemState)
	{
	case OnGround:
	{
		f[0] = &Object::FnHauling;
		btn[0] = ActionBtn::PickUp;
		return 1;
		break;
	}
	case InChest:
	{
		f[0] = &Object::FnGearUp;
		btn[0] = ActionBtn::PickUp;
		return 1;
		break;
	}
	case InInven:
	{
		f[0] = &Object::FnConsuming;
		btn[0] = ActionBtn::Consume;
		return 1;
		break;
	}
	default:
		return 0;
		break;
	}

}

#pragma endregion

#pragma region Plant.h
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
#pragma endregion

#pragma region Plant.cpp
#include "stdafx.h"
#include "Plant.h"
#include "Food.h"

Plant::Plant(Object_List Type) : ImmobileObject(Type)
{
}

Plant::Plant(const Plant & obj) : ImmobileObject(obj)
{
	GrowCycle =(float)(rand() % 2000 + 2000);
	GrowCycle /= 100.0f;
	switch (Type)
	{
	case Wolfsbane:
		meshindex = WOLFSBANE_INDEX;
		SetPassable(true);
		break;
	case Dandelion:
		meshindex = DANDELION_INDEX;
		SetPassable(true);
		break;
	case Marigold:
		meshindex = MARIGOLD_INDEX;
		SetPassable(true);
		break;
	case Rosemary:
		meshindex = ROSEMARY_INDEX;
		SetPassable(true);
		break;
	case Mushroom:
		meshindex = MUSHROOM_INDEX;
		SetPassable(true);
		break;
	case Feybell:
		meshindex = FEYBELL_INDEX;
		SetPassable(true);
		break;
	case Deeproot:
		meshindex = DEEPROOT_INDEX;
		SetPassable(true);
		break;
	case Clover:
		meshindex = CLOVERS_INDEX;
		SetPassable(true);
		break;
	default:
		break;
	}
}

Plant::~Plant()
{
}

Item * Plant::HarvestGrow()
{
	Item* result = (Item*)OM->Create(Product, Pos_n_Matrix.Matrix, PosX, PosY, PosZ);

	return result;
}

void Plant::Update(float Dtime)
{
	if (!FinishGrow)
	{
		GrowTime += Dtime;
		if (GrowTime > GrowCycle)
		{
			GrowTime = 0;
			FinishGrow = true;
		}
	}
}

void Plant::Draw(XMMATRIX Pos)
{
	switch (Type)
	{
	case Wolfsbane:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, XMMatrixMultiply(XMMatrixScaling(2.0f,2.0f,2.0f),Pos));
		break;
	case Dandelion:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, XMMatrixMultiply(XMMatrixScaling(1.5f,1.5f,1.5f),Pos));
		break;
	case Marigold:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, XMMatrixMultiply(XMMatrixScaling(1.5f,1.5f,1.5f),Pos));
		break;
	case Rosemary:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, XMMatrixMultiply(XMMatrixRotationY(1.57f),XMMatrixMultiply(XMMatrixScaling(2.0f,2.0f,2.0f),Pos)));
		break;
	case Mushroom:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, Pos);
		break;
	case Feybell:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, Pos);
		break;
	case Deeproot:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, Pos);
		break;
	case Clover:
		LM->GetGraphicsManager()->AddMeshToDraw(meshindex, Pos);
		break;
	default:
		break;
	}
}

int Plant::RCSetup(Functionptr * f, ActionBtn * btn)
{
	switch (ItemState)
	{
	case OnGround:
	{
		f[0] = &Object::FnHarvest;
		btn[0] = ActionBtn::Harvest;
		return 1;
		break;
	}
	case InChest:
	{
		btn[0] = ActionBtn::PickUp;
		f[0] = &Object::FnGearUp;
		return 1;
		break;
	}
	case InInven:
	{
		btn[0] = ActionBtn::Destroy;
		f[0] = &Object::FnDestroy;
		return 1;
		break;
	}
	default:
		break;
	}
	return 0;
}

Object * Plant::Interact(Jobs job, float Delta, Object * objinput, Object_List make, int count)
{
	Object* result = nullptr;
	if (GetJob() == job)
	{
		switch (job)
		{
		case Farming:
		{
			LM->GetTileMap()->GetTile(PosY, PosX, PosZ)->SetImmobileObject(nullptr);
			Visible = false;
			result = this;
			JobClaim = nullptr;
			result->ItemState = InInven;
			SetJob(None);
			break;
		}
		default:
			DTime = 0;
			break;
		}
	}
	return result;
}

CTree::CTree(Object_List list)
	: Plant(list)
{
	switch (Type)
	{
	case FTree:
	{
		meshindex = OAKTREE_INDEX;
		cangrow = true;
		break;
	}
	case PTree:
		meshindex = TREE_INDEX;
		break;
	case PSTree:
		meshindex = PINE_SNOW_INDEX;
		break;
	}
}

CTree::CTree(Object_List list,Object::Position_and_Matrix p) : Plant(list)
{
	this->Pos_n_Matrix = p;
	switch (Type)
	{
	case FTree:
	{
		meshindex = OAKTREE_INDEX;
		cangrow = true;
		break;
	}
	case PTree:
		meshindex = TREE_INDEX;
		break;
	case PSTree:
		meshindex = PINE_SNOW_INDEX;
		break;
	}
	GrowCycle =(float)(rand() % 2000 + 2000);
	GrowCycle /= 100.0f;
}

CTree::~CTree()
{

}

Item * CTree::HarvestApple()
{
	Item* temp = invenFruit[0];
	invenFruit.erase(invenFruit.begin());
	Plantcount--;
	DTime = 0;
	GrowTime = 0;
	this->SetJob(None);
	FinishGrow = false;
	return temp;
}

Item* CTree::CutWood()
{
	Item* temp = dynamic_cast<Item*>(OM->Create(Log, this->Pos_n_Matrix.Matrix, PosX, PosY, PosZ));
	DEAD = true;
	return temp;
}

void CTree::Update(float Dtime)
{
	if (cangrow&&Plantcount < PlantMax)
	{
		GrowTime += Dtime;
		if (GrowTime > GrowCycle)
		{
			//this->meshindex = OAKTREE_INDEX;
			Plantcount++;
			Food* newfood = (Food*)OM->Create(Apple,Pos_n_Matrix.Matrix,PosX,PosY,PosZ);
			invenFruit.push_back(newfood);
			FinishGrow = true;
		}
	}
	if (DEAD)
		OM->Destroy(this);
}

void CTree::Draw(XMMATRIX Pos)
{
	if (Visible)
	{
		if (Type == FTree)
		{
			//Tree
			XMMATRIX Scale = XMMatrixScaling(0.5f, 1.0f, 0.5f);
			float ratio = GrowTime / GrowCycle;
			//LM->GetGraphicsManager()->AddMeshToDraw(meshindex, XMMatrixMultiply(Scale, Pos));
			LM->GetGraphicsManager()->AddMeshToDraw(meshindex, XMMatrixMultiply(Scale, Pos), XMFLOAT4(1.0f - ratio + 0.5f, 0.874f - ratio * 0.874f + 0.5f, 0.5f*ratio, 1.0f));
			//Apples
			float lerp = 0.3f*ratio;
			Scale = XMMatrixScaling(lerp, lerp, lerp);
			LM->GetGraphicsManager()->AddMeshToDraw(APPLE_INDEX, XMMatrixMultiply(Scale, XMMatrixMultiply(Pos, XMMatrixTranslation(0.0f, 1.8f, -0.45f))));
			LM->GetGraphicsManager()->AddMeshToDraw(APPLE_INDEX, XMMatrixMultiply(Scale, XMMatrixMultiply(Pos, XMMatrixTranslation(0.0f, 2.4f, -0.75f))));
			LM->GetGraphicsManager()->AddMeshToDraw(APPLE_INDEX, XMMatrixMultiply(Scale, XMMatrixMultiply(Pos, XMMatrixTranslation(0.2f, 2.65f, -0.45f))));
			LM->GetGraphicsManager()->AddMeshToDraw(APPLE_INDEX, XMMatrixMultiply(Scale, XMMatrixMultiply(Pos, XMMatrixTranslation(-0.8f, 2.7f, -0.33f))));
			LM->GetGraphicsManager()->AddMeshToDraw(APPLE_INDEX, XMMatrixMultiply(Scale, XMMatrixMultiply(Pos, XMMatrixTranslation(-0.8f, 2.7f, 0.33f))));
			LM->GetGraphicsManager()->AddMeshToDraw(APPLE_INDEX, XMMatrixMultiply(Scale, XMMatrixMultiply(Pos, XMMatrixTranslation(-0.2f, 2.7f, 0.33f))));
			LM->GetGraphicsManager()->AddMeshToDraw(APPLE_INDEX, XMMatrixMultiply(Scale, XMMatrixMultiply(Pos, XMMatrixTranslation(0.5f, 1.8f, 0.33f))));
		}
		else
			LM->GetGraphicsManager()->AddMeshToDraw(meshindex, Pos);
	}
}

Object * CTree::Interact(Jobs job, float Delta, Object * objinput, Object_List make, int count)
{
	Object* result = nullptr;
	if (GetJob() == job)
	{
		switch (job)
		{
		case Farming:
		{
			if (invenFruit.size() >= 0)
			{
				DTime += Delta;
				if (DTime > HarvestTake)
				{
					result = HarvestApple();
					result->ItemState = InInven;
					this->JobClaim = nullptr;
				}
			}
			break;
		}
		case Woodcutting:
		{
			DTime += Delta;
			if (soundonce == false)
			{
				Waudio.SetObjectSoundPos(this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.Z, SoundObject::GAME_OBJECT_ID_TREE);

				Waudio.Reg_Event(AK::EVENTS::PLAY_SAWING_WOOD, SoundObject::GAME_OBJECT_ID_TREE);
				soundonce = true;
			}
			/*XMStoreFloat4x4(&LM->GetGraphicsManager()->PS->WoodCutEmitter->EmitterWM, LM->GetTileMap()->GetTileMatrix(LM->GetTileMap()->GetTile(Pos_n_Matrix.Pos.Y, Pos_n_Matrix.Pos.X, Pos_n_Matrix.Pos.Z)));
			LM->GetGraphicsManager()->PS->WoodCutEmitter->IsActive = true;*/
			if (DTime > WoodCut)
			{
				result = CutWood();
				result->ItemState = InInven;
				//LM->GetGraphicsManager()->PS->WoodCutEmitter->IsActive = false;
				if (this->invenFruit.size() > 0)
					LM->GetTileMap()->GetTile(this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Z)->SetImmobileObject(invenFruit[0]);
				else
					LM->GetTileMap()->GetTile(this->Pos_n_Matrix.Pos.Y, this->Pos_n_Matrix.Pos.X, this->Pos_n_Matrix.Pos.Z)->SetImmobileObject(nullptr);
				LM->GetNotificationManager()->SetObjective(NotificationManager::Objectives::Obj_ChopTree);
			}
			break;
		}
		default:
			DTime = 0;
			break;
		}
	}
	return result;
}

int CTree::RCSetup(Functionptr * f, ActionBtn* btn)
{
	f[0] = &Object::FnWoodCutting;
	btn[0] = ActionBtn::Cut;
	if (Plantcount != 0)
	{
		f[1] = &Object::FnHarvest;
		btn[1] = ActionBtn::Harvest;
		return 2;
	}
	return 1;
}

#pragma endregion