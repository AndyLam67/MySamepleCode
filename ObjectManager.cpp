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
