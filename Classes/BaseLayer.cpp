#include "BaseLayer.h"

bool BaseLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg = Sprite::create("bg/Setting.png");
	float scaleBGtime = visibleSize.height / bg->getContentSize().height;
	bg->setScale(scaleBGtime);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg);

	MenuItemFont::setFontName("Charlemagne Std");
	MenuItemFont::setFontSize(76);
	auto backMenuItem = MenuItemFont::create("BACK", CC_CALLBACK_1(BaseLayer::menuBackCallback, this));
	auto mu = Menu::create(backMenuItem, NULL);
	mu->setPosition(Vec2(visibleSize.width - 300, 150));
	addChild(mu);

	return true;
}

void BaseLayer::menuBackCallback(Ref * pSender)
{
	Director::getInstance()->popScene();
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY))
	{
		SimpleAudioEngine::getInstance()->playEffect(Click_Sound);
	}
}

void BaseLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("BaseLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY))
	{
		SimpleAudioEngine::getInstance()->playBackgroundMusic(Home_BG_Music, true);
	}
}