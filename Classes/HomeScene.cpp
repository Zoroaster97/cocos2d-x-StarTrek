#include "HomeScene.h"

Scene * HomeMenuLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HomeMenuLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HomeMenuLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("bg/Home.png");
	float scaleBGtime = visibleSize.height / bg->getContentSize().height;
	bg->setScale(scaleBGtime);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	addChild(bg);

	auto top = Sprite::createWithSpriteFrameName("StarTrek.png");
	top->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 300));
	addChild(top);

	// 开始菜单
	auto startSpriteNormal = Sprite::createWithSpriteFrameName("play.png");
	auto startSpriteSelected = Sprite::createWithSpriteFrameName("play_on.png");
	auto startMenuItem = MenuItemSprite::create(
		startSpriteNormal,
		startSpriteSelected,
		CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	startMenuItem->setTag(ActionType::MenuItemStart);

	// 设置菜单
	auto settingSpriteNormal = Sprite::createWithSpriteFrameName("setting.png");
	auto settingSpriteSelected = Sprite::createWithSpriteFrameName("setting_on.png");
	auto settingMenuItem = MenuItemSprite::create(
		settingSpriteNormal,
		settingSpriteSelected,
		CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	settingMenuItem->setTag(ActionType::MenuItemSetting);

	// 帮助菜单
	auto helppriteNormal = Sprite::createWithSpriteFrameName("help.png");
	auto helpSpriteSelected = Sprite::createWithSpriteFrameName("help_on.png");
	auto helpMenuItem = MenuItemSprite::create(
		helppriteNormal,
		helpSpriteSelected,
		CC_CALLBACK_1(HomeMenuLayer::menuItemCallback, this));
	helpMenuItem->setTag(ActionType::MenuItemHelp);

	auto mu = Menu::create(startMenuItem, settingMenuItem, helpMenuItem, NULL);

	mu->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	mu->alignItemsHorizontallyWithPadding(20);
	addChild(mu);

	return true;
}

void HomeMenuLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("HomeMenuLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(Home_BG_Music, true);
	}
}

void HomeMenuLayer::menuItemCallback(cocos2d::Ref *sender)
{

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(Click_Sound);
	}
	Scene* tsc = nullptr;

	MenuItem* menuItem = (MenuItem*)sender;
	log("MenuItem Tag = %d", menuItem->getTag());
	switch (menuItem->getTag())
	{
	case ActionType::MenuItemStart:
		tsc = TransitionFade::create(1.0f, GamePlay::createScene());
		log("StartCallback");
		break;
	case ActionType::MenuItemHelp:
		tsc = TransitionFade::create(1.0f, HelpLayer::createScene());
		log("HelpCallback");
		break;
	case ActionType::MenuItemSetting:
		tsc = TransitionFade::create(1.0f, SettingLayer::createScene());
		log("SettingCallback");
		break;
	}
	if (tsc)
		Director::getInstance()->pushScene(tsc);
}