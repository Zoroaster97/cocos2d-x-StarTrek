#include"Spacecraft.h"

Spacecraft* Spacecraft::createWithSpriteFrameName(const char* spriteFrameName)
{
	Spacecraft *spacecraft = new Spacecraft();

	if (spacecraft && spacecraft->initWithSpriteFrameName(spriteFrameName))
	{
		spacecraft->autorelease();

		auto body = PhysicsBody::create();
		body->addShape(PhysicsShapeCircle::create(spacecraft->getContentSize().width / 2 - 5));
		body->setMass(5);
		body->setCategoryBitmask(0x01);			//0001
		body->setCollisionBitmask(0x01);		//0001
		body->setContactTestBitmask(0x01);

		spacecraft->setPhysicsBody(body);

		return spacecraft;
	}

	CC_SAFE_DELETE(spacecraft);

	return NULL;
}

void Spacecraft::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->getPhysicsBody()->setVelocity(this->getPhysicsBody()->getVelocity() + this->getAcce() * dt);

	if (this->getPosition().y < 0) {
		this->setPosition(this->getPosition().x, 0);
		this->getPhysicsBody()->setVelocity(Vec2(this->getPhysicsBody()->getVelocity().x, 0));
	}
	if (this->getPosition().y > visibleSize.height) {
		this->setPosition(this->getPosition().x, visibleSize.height);
		this->getPhysicsBody()->setVelocity(Vec2(this->getPhysicsBody()->getVelocity().x, 0));
	}
	if (this->getPosition().x < 0) {
		this->setPosition(visibleSize.width, this->getPosition().y);
	}
	if (this->getPosition().x > visibleSize.width) {
		this->setPosition(0, this->getPosition().y);
	}
}

void Spacecraft::applyAcce()
{

}

void Spacecraft::resetAcce()
{
	this->setAcce(Vec2(0, 0));
}