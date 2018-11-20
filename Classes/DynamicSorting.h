#pragma once
#include "IsoObject.h"

class DynamicSorting : public cocos2d::Component
{
public:
	DynamicSorting();
	~DynamicSorting();

	void addObject(IsoObject* object);
	void removeObject(IsoObject* object);
	void sort();

	void update(float delta) override;

private:
	bool isBehind(IsoObject* a, IsoObject* b);
	int get_bucket(IsoObject& obj);
	std::map<int, std::vector<IsoObject*>> buckets;
};

