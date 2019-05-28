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
