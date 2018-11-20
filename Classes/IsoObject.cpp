#include "IsoObject.h"





IsoObject::IsoObject(cocos2d::Sprite* sprite)
{
	spritePtr = sprite;
}

IsoObject::~IsoObject()
{
}

void IsoObject::setPosition(const cocos2d::Vec3& position)
{
	this->position = position;
}

cocos2d::Vec3 IsoObject::getPosition() const
{
	return position;
}

void IsoObject::setSize(const cocos2d::Vec3& size)
{
	this->size = size;
}

cocos2d::Vec3 IsoObject::getSize() const
{
	return size;
}

cocos2d::Vec3 IsoObject::getMin() const
{
	return position - size / 2.0f;
}

cocos2d::Sprite* IsoObject::getSprite() const
{
	return spritePtr;
}



bool IsoObject::operator<(const IsoObject& rhs) const
{
	const auto aPos = this->getPosition();
	const auto aSize = this->getSize();
	const auto bPos = rhs.getPosition();
	const auto bSize = rhs.getSize();
	auto aPosX = aPos.x;
	auto aPosZ = aPos.z;
	auto aPosY = aPos.y;

	auto aSizeX = aSize.x;
	auto aSizeZ = aSize.z;
	auto aSizeY = aSize.y;

	auto bPosX = bPos.x;
	auto bPosZ = bPos.z;
	auto bPosY = bPos.y;

	auto bSizeX = bSize.x;
	auto bSizeZ = bSize.z;
	auto bSizeY = bSize.y;

	auto aMaxX = aPosX + aSizeX;
	auto aMaxZ = aPosZ + aSizeZ;
	auto aMaxY = aPosY + aSizeY;

	auto bMaxX = bPosX + bSizeX;
	auto bMaxZ = bPosZ + bSizeZ;
	auto bMaxY = bPosY + bSizeY;

	//AABBs dont intersect and a is behind b
	auto aBehindB = aMaxX > bPosX && aMaxZ > bPosZ && bMaxY > aPosY;
	if (!aBehindB)
		return aBehindB;
	//AABBs dont intersect and b is behind a
	auto bBehindA = bMaxX > aPosX && bMaxZ > aPosZ && aMaxY > bPosY;
	if (!bBehindA)
		return aBehindB;

	//AABBs intersect, find axis with min intersection
	auto distAx = aMaxX - bPosX;
	auto distAz = aMaxZ - bPosZ;
	auto distAy = bMaxY - aPosY;

	auto distBx = bMaxX - aPosX;
	auto distBz = bMaxZ - aPosZ;
	auto distBy = aMaxY - bPosY;

	auto distBAx = distBx - distAx;
	auto distBAz = distBz - distAz;
	auto distBAy = distBy - distAy;

	auto absDistX = aSizeX + bSizeX - (distBAx < 0.0f ? -distBAx : distBAx);
	auto absDistZ = aSizeZ + bSizeZ - (distBAz < 0.0f ? -distBAz : distBAz);
	auto absDistY = aSizeY + bSizeY - (distBAy < 0.0f ? -distBAy : distBAy);

	if (absDistX <= absDistZ && absDistX <= absDistY)
		return distAx > distBx;
	if (absDistZ <= absDistX && absDistZ <= absDistY)
		return distAz > distBz;
	return distAy > distBy;
}

