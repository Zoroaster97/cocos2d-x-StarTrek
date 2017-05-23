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


	//��������
	void createPlanet0(float dt);
	void createPlanet1(float dt);
	void createPlanet2(float dt);
	void createPlanet3(float dt);
	//��������.
	void updateForce(float dt);
	//��ʼ������.
	void initBG();
	void moveBG(float dt);

	//��״̬���и��µ÷�.
	void updateStatusBarScore();

	void menuPauseCallback(cocos2d::Ref* pSender);
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuResumeCallback(cocos2d::Ref* pSender);

	//����ɴ����������ײ���
	void handleSpacecraftCollidingWithPlanet(Planet* planet);

	CREATE_FUNC(GamePlay);
};
#endif // __GAME_PLAY_SCENE_H__