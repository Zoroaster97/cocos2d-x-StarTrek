#ifndef __SPACECRAFT_SPRITE_H__
#define __SPACECRAFT_SPRITE_H__

#include "SystemHeader.h"

#define Spacecraft_Mass 50.0

class Spacecraft : public cocos2d::Sprite
{
	CC_SYNTHESIZE(cocos2d::Vec2, acce, Acce);
	//CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);

public:
	virtual void update(float dt);
	static Spacecraft* createWithSpriteFrameName(const char* spriteFrameName);

	virtual void applyAcce();
	virtual void resetAcce();

};

#endif //__FIGHTER_SPRITE_H__

