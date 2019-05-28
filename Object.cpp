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
