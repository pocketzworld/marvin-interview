#pragma once
#include "math/Mat4.h"
#include "2d/CCComponent.h"

namespace cocos2d {
	class Sprite;
	class Vec3;
}

class IsoObject
{
public:
	explicit IsoObject(cocos2d::Sprite* sprite);
	~IsoObject();
	void setPosition(const cocos2d::Vec3& position);
	cocos2d::Vec3 getPosition() const;
	void setSize(const cocos2d::Vec3& size);
	cocos2d::Vec3 getSize() const;
	cocos2d::Vec3 getMin() const;
	cocos2d::Sprite* getSprite() const;
	bool operator<(const IsoObject& rhs) const;

private:
	cocos2d::Vec3 position;
	cocos2d::Vec3 size;
	cocos2d::Sprite* spritePtr	;
};


