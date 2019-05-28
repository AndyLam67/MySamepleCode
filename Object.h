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
