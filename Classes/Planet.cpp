#include "Planet.h"

Planet::Planet(PlanetTypes planetType)
{
	this->planetType = planetType;
	this->velocity = Vec2::ZERO;
}

Planet* Planet::createWithPlanetTypes(PlanetTypes planetType)
{
	Planet *planet = new Planet(planetType);

	const char* planetFramName = Planet_0;

	switch (planetType) {
	case PlanetType1:
		planetFramName = Planet_0;
		planet->setMass(300);
		break;
	case PlanetType2:
		planetFramName = Planet_1;
		planet->setMass(500);
		break;
	case PlanetType3:
		planetFramName = Planet_2;
		planet->setMass(1000);
		break;
	case PlanetType4:
		planetFramName = Planet_3;
		planet->setMass(1500);
		break;
	}

	if (planet && planet->initWithSpriteFrameName(planetFramName)) {

		planet->autorelease();
		auto body = PhysicsBody::create();

		body->addShape(PhysicsShapeCircle::create(planet->getContentSize().width / 2 - 5));

		body->setCategoryBitmask(0x01);			//0001
		body->setCollisionBitmask(0x01);		//0001
		body->setContactTestBitmask(0x01);

		planet->setPhysicsBody(body);

		planet->setVisible(false);
		planet->spawn();
		planet->unscheduleUpdate();
		planet->scheduleUpdate();

		return planet;
	}

	CC_SAFE_DELETE(planet);

	return nullptr;
}

void Planet::update(float dt)
{
	//ÉèÖÃÐÐÐÇÐý×ª.
	switch (planetType) {
	case PlanetType1:
		this->setRotation(this->getRotation() - 1);
		break;
	case PlanetType2:
		this->setRotation(this->getRotation() + 1);
		break;
	case PlanetType3:
		this->setRotation(this->getRotation() - 0.5);
		break;
	case PlanetType4:
		this->setRotation(this->getRotation() + 0.5);
		break;
	}

	Vec2 moveLen = velocity * dt;

	this->setPosition(this->getPosition() + moveLen);

	if (this->getPosition().y + this->getContentSize().height / 2 < 0) {
		this->spawn();
	}
}


void Planet::spawn()
{
	Size screenSize = Director::getInstance()->getVisibleSize();
	float yPos = screenSize.height + this->getContentSize().height / 2;
	float xPos = CCRANDOM_0_1()*(screenSize.width - this->getContentSize().width) + this->getContentSize().width / 2;
	this->setPosition(Vec2(xPos, yPos));
	this->setAnchorPoint(Vec2(0.5f, 0.5f));

	this->setVisible(true);

}

void Planet::setAcceToSpacecraft(Spacecraft * spacecraft)
{
	auto sc_position = spacecraft->getPosition();
	auto distance = ccpDistance(sc_position, this->getPosition());
	auto acceValue = Constant_G * this->getMass() / (distance*distance);
	auto normal = (this->getPosition() - sc_position).getNormalized();
	Vec2 acce = Vec2(acceValue * normal.x, acceValue * normal.y);
	spacecraft->setAcce(spacecraft->getAcce() + acce);
	//spacecraft->getPhysicsBody()->applyForce(acce * spacecraft->getPhysicsBody()->getMass());
}