#include "HelpScene.h"

Scene* HelpLayer::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelpLayer::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelpLayer::init()
{
	//////////////////////////////
	// 1. super init first
	if (!BaseLayer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto top = Label::createWithSystemFont("HELP", "Charlemagne Std", 80);
	top->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 150));
	addChild(top);

	auto txtTest = Label::createWithSystemFont("Code", "Charlemagne Std", 36);
	txtTest->setColor(Color3B(75, 255, 255));
	txtTest->setPosition(visibleSize.width / 2 - 100, top->getPosition().y - 200);
	txtTest->setAnchorPoint(Vec2(0, 0));
	addChild(txtTest, 1);

	auto test1 = Label::createWithSystemFont("Zoroaster", "Charlemagne Std", 36);
	test1->setAnchorPoint(Vec2(0, 0));
	Vec2 p1 = txtTest->convertToWorldSpace(Vec2(0, -40));
	test1->setPosition(p1);
	addChild(test1, 1);

	auto txtMusic = Label::createWithSystemFont("Picture&Font", "Charlemagne Std", 36);
	txtMusic->setColor(Color3B(75, 255, 255));
	Vec2 p6 = test1->convertToWorldSpace(Vec2(0, -60));
	txtMusic->setPosition(p6);
	txtMusic->setAnchorPoint(Vec2(0, 0));
	addChild(txtMusic, 1);

	auto music1 = Label::createWithSystemFont("HEzz", "Charlemagne Std", 36);
	music1->setAnchorPoint(Vec2(0, 0));
	Vec2 p7 = txtMusic->convertToWorldSpace(Vec2(0, -40));
	music1->setPosition(p7);
	addChild(music1, 1);

	auto music2 = Label::createWithSystemFont("Baijing", "Charlemagne Std", 36);
	music2->setAnchorPoint(Vec2(0, 0));
	Vec2 p8 = music1->convertToWorldSpace(Vec2(0, -40));
	music2->setPosition(p8);
	addChild(music2, 1);

	auto txtSound = Label::createWithSystemFont("Music&Sound", "Charlemagne Std", 36);
	txtSound->setColor(Color3B(75, 255, 255));
	Vec2 p10 = music2->convertToWorldSpace(Vec2(0, -60));
	txtSound->setPosition(p10);
	txtSound->setAnchorPoint(Vec2(0, 0));
	addChild(txtSound, 1);

	auto sound1 = Label::createWithSystemFont("XRC", "Charlemagne Std", 36);
	sound1->setAnchorPoint(Vec2(0, 0));
	Vec2 p11 = txtSound->convertToWorldSpace(Vec2(0, -40));
	sound1->setPosition(p11);
	addChild(sound1, 1);

	return true;
}
