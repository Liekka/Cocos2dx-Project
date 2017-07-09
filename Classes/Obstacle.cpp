#include "Obstacle.h"
#include "resource.h"

bool Obstacle::clockwise = true;

Obstacle::Obstacle()
{
	obstacleList = Array::create();
	obstacleList->retain();
}

void Obstacle::update(float delta)
{
	float rotation = 1 + delta;
	if (!clockwise)
		rotation *= -1;
	if (obstacleList == nullptr)
		return;
	for (int i = obstacleList->count() - 1; i >= 0; i--)
	{
		auto s = (Sprite*)obstacleList->getObjectAtIndex(i);
		s->setRotation(s->getRotation() + rotation);
	}
}

void Obstacle::addOne(int offsetY)
{
	Size visibleSize = Director::getInstance()->getWinSize();
	auto obstacle = Sprite::create(IMG_OBSTACLE);
	obstacle->setScale(0.5);
	Size obstacleSize = obstacle->getContentSize();
	obstacleList->addObject(obstacle);
	this->addChild(obstacle);

	// set positon
	obstacle->setPosition(Vec2(visibleSize.width / 2, offsetY));
	obstacle->setTag(TAG_OBSTACLE);
	cocos2d::log("a obstacle added");
}

void Obstacle::deleteOne()
{
	if (obstacleList == nullptr || obstacleList->count() == 0)
		return;
	auto s = (Sprite*)obstacleList->getObjectAtIndex(0);
	if (s && s->getPositionY() < -s->getContentSize().height / 2) {
		obstacleList->removeObjectAtIndex(0);
		this->removeChild(s);
		cocos2d::log("a obstacle removed");
	}
}

Property Obstacle::getBottomProperty(int index)
{
	auto obstacle = (Sprite *)obstacleList->getObjectAtIndex(index);
	auto rotation = (int)(obstacle->getRotation()) % 360;
	// deal with negative rotaion angle
	if (rotation < 0)
		rotation += 360;
	return getPropertyByRotation(rotation);
}

Property Obstacle::getTopProperty(int index)
{
	auto obstacle = (Sprite *)obstacleList->getObjectAtIndex(index);
	// Suppose that the obstacle ratates another half circle
	auto rotation = (int)(obstacle->getRotation() + 180) % 360;
	// deal with negative rotaion angle
	if (rotation < 0)
		rotation += 360;
	return getPropertyByRotation(rotation);
}

Property Obstacle::getPropertyByRotation(int rotation)
{
	Property ret;
	if ((rotation >= 0 && rotation < CIRCLE_SHUI_MIN) || rotation >= CIRCLE_SHUI_MAX)
		ret =  Shui;
	else if (rotation >= CIRCLE_MU_MIN && rotation < CIRCLE_MU_MAX)
		ret =  Mu;
	else if (rotation >= CIRCLE_JIN_MIN && rotation < CIRCLE_JIN_MAX)
		ret =  Jin;
	else if (rotation >= CIRCLE_HUO_MIN && rotation < CIRCLE_HUO_MAX)
		ret =  Huo;
	else if (rotation >= CIRCLE_TU_MIN && rotation < CIRCLE_TU_MAX)
		ret =  Tu;
	log("color: %d", ret);

	return ret;
}
