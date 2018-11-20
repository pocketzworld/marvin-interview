#include "DynamicSorting.h"
#include "2d/CCSprite.h"


/*
 * Responsible for sorting IsoObjects on a per frame basis. Similar to painters. Works kind of like bucket sort
 */
DynamicSorting::DynamicSorting()
{
}


DynamicSorting::~DynamicSorting()
{
}


void DynamicSorting::addObject(IsoObject* object)
{
	auto index = get_bucket(*object);
	auto bucket = buckets[index];
	bucket.push_back(object);
}

void DynamicSorting::removeObject(IsoObject* object)
{
	auto index = get_bucket(*object);
	auto bucket = buckets[index];
	bucket.erase(std::remove(bucket.begin(), bucket.end(), object), bucket.end());
}

void DynamicSorting::sort()
{
	int i = 10000;
	//go over each bucket
	for (auto it = buckets.begin(); it != buckets.end();)
	{
		std::vector<IsoObject*> bucket = it->second;
		//partially sort bucket
		std::sort(bucket.begin(), bucket.end());
		for (auto innerIt = bucket.begin(); innerIt != bucket.end();)
		{
			//apply zOrder
			(*innerIt)->getSprite()->setGlobalZOrder(i--);
		}
	}
}

void DynamicSorting::update(float delta)
{
	sort();
}


/**
 * Determines given two objects, if a is behind b => draw a, then b. 
 * This is proprietary stuff, please make sure this doesn't get public
 */
bool DynamicSorting::isBehind(IsoObject* a, IsoObject* b)
{
	const auto aPos = a->getPosition();
	const auto aSize = a->getSize();
	const auto bPos = b->getPosition();
	const auto bSize = b->getSize();
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

/*
 * maps the 2d space (ground plane) on a 1d space (bucket indices)
 */
int DynamicSorting::get_bucket(IsoObject& obj)
{
	const auto min = obj.getMin();
	return static_cast<int>(floor(min.x + .5f) + floor(min.z + .5f));

}

