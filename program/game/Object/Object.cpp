#include "Object.h"
#include"../Manager/GameManager.h"

Object::Object()
{
	gManager = GameManager::Instance();
	
}

void Object::SetList()
{
	gManager->AddObjectList(shared_from_this());
}
