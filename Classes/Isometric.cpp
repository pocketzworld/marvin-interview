#include "Isometric.h"
#include "math/Quaternion.h"
#include "spine/extension.h"


cocos2d::Mat4 getProjMat()
{
	cocos2d::Mat4 mat = cocos2d::Mat4::IDENTITY;
	const double degToRad = 1 / (180 / M_PI);
	// mat.rotate(cocos2d::Vec3(1,0,0),-45 * degToRad);
	// mat.rotateY(-35.625f * degToRad);
	mat.rotateX(-35.625f * degToRad);
	mat.rotateY(-45.0f * degToRad);
	return mat;
}

cocos2d::Mat4 Isometric::projectionMat = getProjMat();

Isometric::Isometric()
{
}


Isometric::~Isometric()
{
}

/*
 * projects from 3d isometric position to 2d screen position
 */
cocos2d::Vec2 Isometric::project(cocos2d::Vec3& worldPos)
{		
	const auto res = projectionMat * worldPos;
	return cocos2d::Vec2(res.x, res.y);
}
