#pragma once
#include "math/Vec2.h"

namespace cocos2d {
	class Vec3;
}

class Isometric
{
public:
	Isometric();
	~Isometric();

	static cocos2d::Vec2 project(cocos2d::Vec3& worldPos);

private:
	static cocos2d::Mat4 projectionMat;
	
};

