#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	///////////////////////////////////////////////
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/loading_texture.plist");

	// add "HelloWorld" splash screen"
	auto bg = Sprite::create("bg/Loading.png");
	float scaleBGtime = visibleSize.height / bg->getContentSize().height;
	bg->setScale(scaleBGtime);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	// add the sprite as a child to this layer
	this->addChild(bg);

	auto sprite = Sprite::createWithSpriteFrameName("loading3.png");
	this->addChild(sprite);
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 100 ));

	///////////////动画开始//////////////////////
	Animation* animation = Animation::create();
	for (int i = 1; i <= 3; i++)
	{
		__String *frameName = __String::createWithFormat("loading%d.png", i);
		log("frameName = %s", frameName->getCString());
		SpriteFrame *spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName->getCString());
		animation->addSpriteFrame(spriteFrame);
	}

	animation->setDelayPerUnit(0.5f);           //设置两个帧播放时间
	animation->setRestoreOriginalFrame(true);    //动画执行后还原初始状态

	Animate* action = Animate::create(animation);
	sprite->runAction(RepeatForever::create(action));
	//////////////////动画结束///////////////////

	m_nNumberOfLoaded = 0;

	Director::getInstance()->getTextureCache()->addImageAsync("texture/home_texture.png",
		CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("texture/setting_texture.png",
		CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));

	Director::getInstance()->getTextureCache()->addImageAsync("texture/gameplay_texture.png",
		CC_CALLBACK_1(HelloWorld::loadingTextureCallBack, this));


	_loadingAudioThread = new std::thread(&HelloWorld::loadingAudio, this);

	//////////////////////////////////////

	return true;
}

void HelloWorld::loadingTextureCallBack(Texture2D *texture)
{

	switch (m_nNumberOfLoaded++)
	{
	case 0:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/home_texture.plist", texture);
		log("home textrue ok.");
		break;
	case 1:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/setting_texture.plist", texture);
		log("setting textrue ok.");
		break;
	case 2:
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("texture/gameplay_texture.plist", texture);
		log("gamepla textrue ok.");
		this->schedule(schedule_selector(HelloWorld::delayCall), 1, 1, 3);
		break;
	}

}

void HelloWorld::delayCall(float dt)
{
	auto sc = HomeMenuLayer::createScene();
	Director::getInstance()->replaceScene(sc);
}

void HelloWorld::loadingAudio()
{
	log("loadAudio");
	//初始化 音乐
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(Home_BG_Music);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(GamePlay_BG_Music);
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic(GameOver_BG_Music);

}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	log("HomeMenuLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(Loading_BG_Music, true);
	}
}

void HelloWorld::onExit()
{
	Layer::onExit();
	_loadingAudioThread->join();
	CC_SAFE_DELETE(_loadingAudioThread);
	SpriteFrameCache::getInstance()->removeSpriteFramesFromFile("texture/loading_texture.plist");
	Director::getInstance()->getTextureCache()->removeTextureForKey("texture/loading_texture.png");
	this->unschedule(schedule_selector(HelloWorld::delayCall));
}