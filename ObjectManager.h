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
