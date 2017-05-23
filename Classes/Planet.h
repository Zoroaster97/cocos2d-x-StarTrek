#ifndef __PLANET_SPRITE_H__
#define __PLANET_SPRITE_H__

#include "SystemHeader.h"
#include "Spacecraft.h"

//定义行星名称 也是行星精灵帧的名字
#define Planet_0 "planet0.png"
#define Planet_1 "planet1.png"
#define Planet_2 "planet2.png"
#define Planet_3 "planet3.png"

//定义行星类型
typedef enum
{
	PlanetType1 = 0,     //陨石
	PlanetType2,      //敌机1   
	PlanetType3,      //敌机2
	PlanetType4       //行星
} PlanetTypes;

#define Constant_G 30000

class Planet : public cocos2d::Sprite
{
	CC_SYNTHESIZE(PlanetTypes, planetType, PlanetType);
	CC_SYNTHESIZE(float, mass, Mass);
	CC_SYNTHESIZE(float, radius, Radius);
	CC_SYNTHESIZE(cocos2d::Vec2, velocity, Velocity);

public:
	Planet(PlanetTypes enemyType);
	void spawn();
	virtual void update(float dt);
	virtual void setAcceToSpacecraft(Spacecraft * spacecraft);
	static Planet* createWithPlanetTypes(PlanetTypes planetType);
};

#endif //__PLANET_SPRITE_H__
