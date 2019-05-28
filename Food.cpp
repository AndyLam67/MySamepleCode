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
