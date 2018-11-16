#pragma once
#include "math/Mat4.h"

namespace cocos2d {
	class Vec3;
}

class IsoObject
{
public:
	IsoObject();
	~IsoObject();
	void setPosition(const cocos2d::Vec3& position);
	cocos2d::Vec3 getPosition();
	void setSize(const cocos2d::Vec3& size);
	cocos2d::Vec3 getSize();


private:
	cocos2d::Vec3 position;
	cocos2d::Vec3 size;


};


