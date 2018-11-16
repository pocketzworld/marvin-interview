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
	cocos2d::Mat4 mat = cocos2d::Mat4::IDENTITY;
	const double degToRad = 180 / M_PI;
	// mat.rotateX(-45 * degToRad);
	// mat.rotateY(-35.625f * degToRad);

	// Quaternion.AngleAxis(-xRot, Vector3.right)*Quaternion.AngleAxis(-yRot, Vector3.up)
	mat.rotate(cocos2d::Quaternion(cocos2d::Vec3::UNIT_X, -45 * degToRad) * cocos2d::Quaternion(cocos2d::Vec3::UNIT_Y, -35.625f * degToRad));

	auto res = mat * worldPos;
	return cocos2d::Vec2(res.x, res.y);
}
