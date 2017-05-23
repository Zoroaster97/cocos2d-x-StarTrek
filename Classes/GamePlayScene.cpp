#include "GamePlayScene.h"

Scene* GamePlay::createScene()
{
	auto scene = Scene::createWithPhysics();
	PhysicsWorld* phyWorld = scene->getPhysicsWorld();
	//phyWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	phyWorld->setGravity(Vect(0, 0));
	auto layer = GamePlay::create();
	scene->addChild(layer);
	return scene;
}

bool GamePlay::init()
{
	if (!Layer::init())
	{
		return false;
	}

	this->initBG();

	return true;
}

void GamePlay::onEnter()
{
	Layer::onEnter();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ʼ����ͣ��ť.
	auto pauseSprite = Sprite::createWithSpriteFrameName("pause.png");
	auto pauseMenuItem = MenuItemSprite::create(pauseSprite, pauseSprite,  CC_CALLBACK_1(GamePlay::menuPauseCallback, this));
	auto pauseMenu = Menu::create(pauseMenuItem, NULL);
	pauseMenu->setPosition(Vec2(120, visibleSize.height - 120));
	this->addChild(pauseMenu, 20, 999);

	//��ҵķɴ�.
	this->spacecraft = Spacecraft::createWithSpriteFrameName("spacecraft.png");
	this->spacecraft->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->spacecraft->getPhysicsBody()->setVelocity(Vec2(0, 0));
	this->addChild(this->spacecraft, 10, GameSceneNodeTagSpacecraft);

	scheduleOnce(schedule_selector(GamePlay::createPlanet0), 2.0f);
	scheduleOnce(schedule_selector(GamePlay::createPlanet1), 5.0f);
	scheduleOnce(schedule_selector(GamePlay::createPlanet2), 10.0f);
	scheduleOnce(schedule_selector(GamePlay::createPlanet3), 20.0f);

	//ע�� �����ɴ��¼�������
	keyboardListener = EventListenerKeyboard::create();
	//�ƶ��ɴ�
	keyboardListener->onKeyPressed = [](EventKeyboard::KeyCode keycode, Event* event) {
		// �ƶ�����
		auto target = event->getCurrentTarget();
		
		switch (keycode)
		{
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			//target->getPhysicsBody()->applyImpulse(Vec2(0, 100));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(0, 400));
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			//target->getPhysicsBody()->applyImpulse(Vec2(0, -100));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(0, -400));
			break;
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			//target->getPhysicsBody()->applyImpulse(Vec2(-100, 0));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(-400, 0));
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			//target->getPhysicsBody()->applyImpulse(Vec2(100, 0));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(400, 0));
			break;
		case EventKeyboard::KeyCode::KEY_W:
			//target->getPhysicsBody()->applyImpulse(Vec2(0, 100));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(0, 100));
			break;
		case EventKeyboard::KeyCode::KEY_S:
			//target->getPhysicsBody()->applyImpulse(Vec2(0, -100));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(0, -100));
			break;
		case EventKeyboard::KeyCode::KEY_A:
			//target->getPhysicsBody()->applyImpulse(Vec2(-100, 0));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(-100, 0));
			break;
		case EventKeyboard::KeyCode::KEY_D:
			//target->getPhysicsBody()->applyImpulse(Vec2(100, 0));
			target->getPhysicsBody()->setVelocity(target->getPhysicsBody()->getVelocity() + Vec2(100, 0));
			break;
		default:
			break;
		}
	};

	// ��� �����ɴ��¼�������
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this->spacecraft);

	//ע�� ��ײ�¼�������
	contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = [this](PhysicsContact& contact)
	{
		auto spriteA = contact.getShapeA()->getBody()->getNode();
		auto spriteB = contact.getShapeB()->getBody()->getNode();
		Node* planet1 = nullptr;

		log("A = %d  ------------ B = %d", spriteA->getTag(), spriteB->getTag());
		if (spriteA->getTag() == GameSceneNodeTagSpacecraft && spriteB->getTag() == GameSceneNodeBatchTagPlanet)
		{
			planet1 = spriteB;
		}
		if (spriteA->getTag() == GameSceneNodeBatchTagPlanet && spriteB->getTag() == GameSceneNodeTagSpacecraft)
		{
			planet1 = spriteA;
		}
		if (planet1 != nullptr) //������ײ
		{
			this->handleSpacecraftCollidingWithPlanet((Planet*)planet1);
			return true;
		}
		return true;
	};

	eventDispatcher->addEventListenerWithFixedPriority(contactListener, 1);

	//ÿ0.1s ����updateForce�������·ɴ��������.
	this->schedule(schedule_selector(GamePlay::updateForce), 0.1f);
	this->schedule(schedule_selector(GamePlay::moveBG), 0.05f);

	this->score = 0;
	this->scorePlaceholder = 0;

	//��״̬������ʾ�÷�
	this->updateStatusBarScore();
}

void GamePlay::createPlanet0(float dt)
{
	auto planet1 = Planet::createWithPlanetTypes(PlanetType1);
	planet1->setVelocity(Vec2(0, -100));
	this->planets.pushBack(planet1);
	this->addChild(planet1, 10, GameSceneNodeBatchTagPlanet);
}

void GamePlay::createPlanet1(float dt)
{
	auto planet2 = Planet::createWithPlanetTypes(PlanetType2);
	planet2->setVelocity(Vec2(0, -100));
	this->planets.pushBack(planet2);
	this->addChild(planet2, 10, GameSceneNodeBatchTagPlanet);
}

void GamePlay::createPlanet2(float dt)
{
	auto planet3 = Planet::createWithPlanetTypes(PlanetType3);
	planet3->setVelocity(Vec2(0, -100));
	this->planets.pushBack(planet3);
	this->addChild(planet3, 10, GameSceneNodeBatchTagPlanet);
}

void GamePlay::createPlanet3(float dt)
{
	auto planet4 = Planet::createWithPlanetTypes(PlanetType4);
	planet4->setVelocity(Vec2(0, -100));
	this->planets.pushBack(planet4);
	this->addChild(planet4, 10, GameSceneNodeBatchTagPlanet);
}

void GamePlay::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	log("GamePlayLayer onEnterTransitionDidFinish");
	UserDefault *defaults = UserDefault::getInstance();
	if (defaults->getBoolForKey(MUSIC_KEY)) {
		SimpleAudioEngine::getInstance()->playBackgroundMusic(GamePlay_BG_Music, true);
	}
}

void GamePlay::onExit()
{
	Layer::onExit();
	//ֹͣ���ø���������.
	this->unschedule(schedule_selector(GamePlay::updateForce));
	this->unschedule(schedule_selector(GamePlay::moveBG));
	planets.clear();
	//ע���¼�������.
	Director::getInstance()->getEventDispatcher()->removeEventListener(keyboardListener);
	Director::getInstance()->getEventDispatcher()->removeEventListener(contactListener);

	this->spacecraft->getPhysicsBody()->resetForces();

	auto nodes = this->getChildren();
	for (const auto& node : nodes) {
		//����Ǳ���������remove
		if (node->getTag() != GameSceneNodeBatchTagBackground && node->getTag() != GameSceneNodeBatchTagBackground0)
		{
			this->removeChild(node);
		}
	}
}

//��ʼ����Ϸ����.
void GamePlay::initBG()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//��ӱ�����ͼ.
	auto bg = Sprite::create("bg/GamePlay.png");
	float scaleBGtime = visibleSize.height / bg->getContentSize().height;
	bg->setScale(scaleBGtime);
	auto bg0 = Sprite::create("bg/GamePlay.png");
	bg0->setScale(scaleBGtime);
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	bg0->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + visibleSize.height));
	this->addChild(bg, 0, GameSceneNodeBatchTagBackground);
	this->addChild(bg0, 0, GameSceneNodeBatchTagBackground0);

}

//�ɴ���������
void GamePlay::updateForce(float dt)
{
	if (spacecraft && spacecraft->isVisible())
	{
		// ���ü��ٶ�
		this->spacecraft->resetAcce();
		
		for (Vector<Planet*>::const_iterator it = this->planets.begin(); it != this->planets.end(); ++it)
		{
			Planet * planet = *it;
			planet->setAcceToSpacecraft(this->spacecraft);
		}
		
	}
	// ���ӵ÷�
	this->score++;
	updateStatusBarScore();
}

void GamePlay::moveBG(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 moveLen =  Vec2(0, -100)* dt;
	auto bg = this->getChildByTag(GameSceneNodeBatchTagBackground);
	auto bg0 = this->getChildByTag(GameSceneNodeBatchTagBackground0);
	bg->setPosition(bg->getPosition() + moveLen);
	bg0->setPosition(bg0->getPosition() + moveLen);
	if (bg->getPosition().y + bg->getContentSize().height / 2 < 0) {
		bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + visibleSize.height));
	}
	if (bg0->getPosition().y + bg0->getContentSize().height / 2 < 0) {
		bg0->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + visibleSize.height));
	}
}

//��״̬������ʾ�÷�
void GamePlay::updateStatusBarScore()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Node* n = this->getChildByTag(GameSceneNodeTagStatusBarScore);
	if (n) 
	{
		this->removeChildByTag(GameSceneNodeTagStatusBarScore);
	}

	if (this->score <0)
		this->score = 0;

	__String * score = __String::createWithFormat("%d", this->score);
	auto lblScore = Label::createWithSystemFont(score->getCString(), "Charlemagne Std", 48);

	lblScore->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 28));
	this->addChild(lblScore, 20, GameSceneNodeTagStatusBarScore);
}

void GamePlay::menuPauseCallback(Ref* pSender)
{
	log("menuPauseCallback");
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(Click_Sound);
	}

	//��ͣ��ǰ���е�node
	this->pause();

	for (const auto& node : this->getChildren())
	{
		node->pause();
	}

	keepSpacecraftAcce = spacecraft->getAcce();
	spacecraft->setAcce(Vec2(0, 0));

	keepSpacecraftVelocity = spacecraft->getPhysicsBody()->getVelocity();
	spacecraft->getPhysicsBody()->setVelocity(Vec2(0, 0));

	Size visibleSize = Director::getInstance()->getVisibleSize();

	//�������˵�

	MenuItemFont::setFontName("Charlemagne Std");
	MenuItemFont::setFontSize(76);

	auto backMenuItem = MenuItemFont::create("BACK", CC_CALLBACK_1(GamePlay::menuBackCallback, this));

	//������Ϸ�˵�
	auto resumeMenuItem = MenuItemFont::create("RESUME", CC_CALLBACK_1(GamePlay::menuResumeCallback, this));

	menu = Menu::create(backMenuItem, resumeMenuItem, NULL);
	menu->alignItemsVerticallyWithPadding(50);
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	addChild(menu, 20, 1000);

}

void GamePlay::menuBackCallback(Ref* pSender)
{
	log("menuBackCallback");
	Director::getInstance()->popScene();
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(Click_Sound);
	}
}

void GamePlay::menuResumeCallback(Ref* pSender)
{
	log("menuResumeCallback");
	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(Click_Sound);
	}
	this->resume();

	for (const auto& node : this->getChildren())
	{
		node->resume();
	}

	spacecraft->setAcce(keepSpacecraftAcce);
	spacecraft->getPhysicsBody()->setVelocity(keepSpacecraftVelocity);

	removeChild(menu);
}


//����ɴ����������ײ���
void GamePlay::handleSpacecraftCollidingWithPlanet(Planet* planet)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	if (UserDefault::getInstance()->getBoolForKey(SOUND_KEY)) {
		SimpleAudioEngine::getInstance()->playEffect(Crash_Sound);
	}

	log("GameOver");

	auto gameOverLayer = GameOverLayer::createWithScore(score);
	auto gameOverScene = Scene::create();
	gameOverScene->addChild(gameOverLayer);

	auto tsc = TransitionFade::create(1.0f, gameOverScene);
	Director::getInstance()->pushScene(tsc);

}