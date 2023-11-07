#include "entity.h"


Vector2f PADDLE_INIT_POS = Vector2f(400, 550);
float PADDLE_SPEED = 288.0f;

Vector2f BALL_INIT_POS = Vector2f(400, 300);
Vector2f BALL_SCALE = Vector2f(0.1f, 0.1f);
float BALL_SPEED = 300.0f;
float START_ANGLE = PI / 1.7;
float MAP_END = 600;
float MAP_BOTTOM = 575;



Vector2f FIRST_BRICK_POS = Vector2f(0, 100);
Vector2f BRICK_SIZE = Vector2f(75.f, 25.f);

void Entity::setStatus(bool status)
{
	this->is_existing = status;
}
void Entity::changeStatus()
{
	this->is_existing = !this->is_existing;
}

bool Entity::getStatus()
{
	return this->is_existing;
}
