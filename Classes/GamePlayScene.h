#ifndef __GAME_PLAY_SCENE_H__
#define __GAME_PLAY_SCENE_H__

#include "SystemHeader.h"
#include"Planet.h"
#include"Spacecraft.h"
#include"GameOverScene.h"

#define GameSceneNodeTagStatusBarScore				300
#define GameSceneNodeBatchTagBackground				800
#define GameSceneNodeBatchTagBackground0				801
#define GameSceneNodeTagSpacecraft						900
#define GameSceneNodeBatchTagPlanet					901

class GamePlay : public cocos2d::Layer
{
private:
	Spacecraft* spacecraft;
	Vec2 keepSpacecraftAcce;
	Vec2 keepSpacecraftVelocity;
	Vector<Planet*> planets;
	Menu* menu;
	int score;
	int scorePlaceholder;
	EventListenerKeyboard *keyboardListener;
	EventListenerPhysicsContact * contactListener;

public:
	static Scene * createScene();

	virtual bool init();
	virtual void onExit();
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();


	//创建行星
	void createPlanet0(float dt);
	void createPlanet1(float dt);
	void createPlanet2(float dt);
	void createPlanet3(float dt);
	//更新受力.
	void updateForce(float dt);
	//初始化背景.
	void initBG();
	void moveBG(float dt);

	//在状态栏中更新得分.
	void updateStatusBarScore();

	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuResumeCallback(cocos2d::Ref* pSender);

	//处理飞船与天体的碰撞检测
	void handleSpacecraftCollidingWithPlanet(Planet* planet);

	CREATE_FUNC(GamePlay);
};
#endif // __GAME_PLAY_SCENE_H__