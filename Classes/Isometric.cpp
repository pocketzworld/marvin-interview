#include "Isometric.h"
#include "math/Quaternion.h"
#include "spine/extension.h"


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
	//verified to work
	//var mat = Matrix4x4.Rotate(Quaternion.AngleAxis(-35.625f, Vector3.right) * Quaternion.AngleAxis(-45, Vector3.up));
		
	cocos2d::Mat4 mat = cocos2d::Mat4::IDENTITY;
	const double degToRad = 180 / M_PI;
	// mat.rotate(cocos2d::Vec3(1,0,0),-45 * degToRad);
	// mat.rotateY(-35.625f * degToRad);
	mat.rotate(cocos2d::Quaternion(cocos2d::Vec3(1, 0, 0), -35.625f * degToRad) * cocos2d::Quaternion(cocos2d::Vec3(0, 1, 0), -45 * degToRad));
	auto res = mat * worldPos;
	return cocos2d::Vec2(res.x, res.y);
}
