#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "SystemHeader.h"

class GameOverLayer : public cocos2d::Layer
{
	int score;
public:

	GameOverLayer(int score);

	virtual bool init();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

	static GameOverLayer* createWithScore(int score);
};

#endif // __GAMEOVER_SCENE_H__