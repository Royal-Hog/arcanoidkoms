

#ifndef PADDLE_H
#define PADDLE_H
#include "entity.h"
#include <SFML/Graphics.hpp>

using namespace sf;

enum struct Direct { NONEDIR, UP, DOWN, LEFT, RIGHT };
extern Vector2f ZERO_VECTOR;
class Paddle : public Entity
{
public:
	void setDirection(Direct direction);
	Direct getDirection();
	Paddle(Texture& texture);
	 ~Paddle() override = default;
	void updateDirection();
	Vector2f updatePaddle(float elapsed_time);
private:
	Direct direction;
};
#endif 