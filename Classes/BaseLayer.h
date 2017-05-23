#pragma once
#include "SystemHeader.h"

class BaseLayer : public cocos2d::Layer
{
public:
	virtual bool init();
	void menuBackCallback(cocos2d::Ref* pSender);
	void onEnterTransitionDidFinish();
};