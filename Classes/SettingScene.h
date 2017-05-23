#ifndef __Setting_SCENE_H__
#define __Setting_SCENE_H__

#include "SystemHeader.h"

#include "BaseLayer.h"

class SettingLayer : public BaseLayer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	void menuSoundToggleCallback(cocos2d::Ref* pSender);
	void menuMusicToggleCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(SettingLayer);
};

#endif // __Setting_SCENE_H__