#include "IsoObject.h"



IsoObject::IsoObject()
{
}


IsoObject::~IsoObject()
{
}

void IsoObject::setPosition(const cocos2d::Vec3& position)
{
	this->position = position;
}

cocos2d::Vec3 IsoObject::getPosition()
{
	return position;
}

void IsoObject::setSize(const cocos2d::Vec3& size)
{
	this->size = size;
}

cocos2d::Vec3 IsoObject::getSize()
{
	return size;
}



