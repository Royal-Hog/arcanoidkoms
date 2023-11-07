#include "paddle.h"

Vector2f ZERO_VECTOR = Vector2f(0.0f, 0.0f);

void Paddle::setDirection(Direct direction)
{
	this->direction = direction;
}

Direct Paddle::getDirection()
{
	return this->direction;
}

Paddle::Paddle(Texture& texture)
{
	this->setPosition(PADDLE_INIT_POS);
	this->setDirection(Direct::NONEDIR);
	this->setStatus(true);
	this->setTexture(texture);
}
Paddle::Paddle()
{

	
}

void Paddle::updateDirection()
{
	if (Keyboard::isKeyPressed(Keyboard::Left)) this->setDirection(Direct::LEFT);
	if (Keyboard::isKeyPressed(Keyboard::Right)) this->setDirection(Direct::RIGHT);
}
Vector2f Paddle::updatePaddle(float elapsed_time)
{
	float absolute_offset = PADDLE_SPEED * elapsed_time;
	Vector2f offset = ZERO_VECTOR;
	if (this->getDirection() == Direct::LEFT) offset = Vector2f(-absolute_offset, 0.0f);
	if (this->getDirection() == Direct::RIGHT) offset = Vector2f(absolute_offset, 0.0f);
	this->move(offset);
	this->setDirection(Direct::NONEDIR);
	return offset;
}