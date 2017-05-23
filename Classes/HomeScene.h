#ifndef __HOME_SCENE_H__
#define __HOME_SCENE_H__

typedef enum {
	MenuItemStart,
	MenuItemSetting,
	MenuItemHelp
} ActionType;

#include "SettingScene.h"
#include "HelpScene.h"
#include "GamePlayScene.h"
#include "SystemHeader.h"

class HomeMenuLayer : public cocos2d::Layer
{
public:
	static cocos2d::Scene * createScene();

	virtual bool init();
	virtual void onEnterTransitionDidFinish();

	void menuItemCallback(cocos2d::Ref * sender);
	CREATE_FUNC(HomeMenuLayer);
};

#endif // __HOME_SCENE_H__