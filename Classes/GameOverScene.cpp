#include "GameOverScene.h"

GameOverLayer::GameOverLayer(int score)
{
	this->score = score;
}

GameOverLayer* GameOverLayer::createWithScore(int score)
{
	GameOverLayer *gover = new GameOverLayer(score);

	if (gover && gover->init()) {
		gover->autorelease();
		return gover;
	}
	CC_SAFE_DELETE(gover);
	return nullptr;
}

bool GameOverLayer::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("bg/GameOver.png");
	float scaleBGtime = visibleSize.height / bg->getContentSize().height;
	bg->setScale(scaleBGtime);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(bg);

	UserDefault *defaults = UserDefault::getInstance();
	int highScore = defaults->getIntegerForKey(HIGHSCORE_KEY);
	if (highScore < score) {
		highScore = score;
		defaults->setIntegerForKey(HIGHSCORE_KEY, highScore);
	}
	__String *text = __String::createWithFormat("%i points", highScore);
	__String *ctext = __String::createWithFormat("%i points", score);

	auto lblCurrentScore = Label::createWithSystemFont("Current Score", "Charlemagne Std", 80);
	lblCurrentScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 400));
	addChild(lblCurrentScore);

	auto lblCurrentScoreValue = Label::createWithSystemFont(ctext->getCString(), "Charlemagne Std", 76);
	lblCurrentScoreValue->setColor(Color3B(75, 255, 255));
	lblCurrentScoreValue->setPosition(lblCurrentScore->getPosition() - Vec2(0, 120));
	addChild(lblCurrentScoreValue);

	auto lblHighestScore = Label::createWithSystemFont("Highest Score", "Charlemagne Std", 80);
	lblHighestScore->setPosition(lblCurrentScoreValue->getPosition() - Vec2(0, 120));
	addChild(lblHighestScore);

	auto lblHighestScoreValue = Label::createWithSystemFont(text->getCString(), "Charlemagne Std", 76);
	lblHighestScoreValue->setColor(Color3B(75, 255, 255));
	lblHighestScoreValue->setPosition(lblHighestScore->getPosition() - Vec2(0, 120));
	addChild(lblHighestScoreValue);

	auto text2 = Label::createWithSystemFont("Tap the Screen to Play", "Charlemagne Std", 76);
	text2->setPosition(lblHighestScoreValue->getPosition() - Vec2(0, 120));
	addChild(text2);

	//×¢²á ´¥ÃþÊÂ¼þ¼àÌýÆ÷
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = [](Touch* touch, Event* event) {
		Director::getInstance()->popScene();
		if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
			SimpleAudioEngine::getInstance()->playEffect(Click_Sound);
		}
		return false;
	};

	// Ìí¼Ó ´¥ÃþÊÂ¼þ¼àÌýÆ÷
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

void GameOverLayer::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("HomeMenuLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(GameOver_BG_Music, true);
	}
}


void GameOverLayer::onExit()
{
	Layer::onExit();
	Director::getInstance()->getEventDispatcher()->removeEventListenersForTarget(this);
}