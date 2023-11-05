#include "ball.h"
#include "game.h"
#include "bonus.h"
#include <iostream>



void Ball::setAngle(float angle)
{
	this->angle = angle;
}
float Ball::getAngle()
{
	return this->angle;
}
Ball::Ball(Texture& texture)
{
	this->setPosition(BALL_INIT_POS);
	this->setAngle(START_ANGLE);
	this->setStatus(true);
	this->setTexture(texture);
	this->setScale(BALL_SCALE);
}
void Ball::checkWallCollision(Vector2f& new_offset_vector, float micro_step, Game& game)
{
	if (this->getPosition().y <= 0)
	{
		this->setAngle(-this->getAngle());
		new_offset_vector = PolarToDSC(micro_step, this->getAngle());
	}
	if (this->getPosition().x <= 0 || this->getPosition().x >= WINDOW_WIDTH)
	{
		this->setAngle(PI - this->getAngle());
		new_offset_vector = PolarToDSC(micro_step, this->getAngle());
	}

	if (game.getBAP() && this->getPosition().y >= MAP_BOTTOM)
	{
		
		if (atan(new_offset_vector.y / new_offset_vector.x) < 0) {

			this->setAngle(2 * PI + atan(new_offset_vector.y / new_offset_vector.x));
		}
		else {
			this->setAngle(PI + atan(new_offset_vector.y / new_offset_vector.x));
		}
		game.setBAP(false);
	}
}
void Ball::checkPaddleCollision(FloatRect& paddle_bounds, Vector2f paddle_offset, Vector2f& new_offset_vector, float micro_step)
{
	FloatRect ball_bounds = this->getGlobalBounds();
	FloatRect next_ball_bounds = MoveRect(ball_bounds, PolarToDSC(micro_step, this->getAngle()));

	if (next_ball_bounds.intersects(paddle_bounds))
	{
		Vector2f ball_offset = PolarToDSC(micro_step, -this->getAngle());
		new_offset_vector = VectorSum(ball_offset, ball_offset);
		new_offset_vector = VectorSum(new_offset_vector, paddle_offset);
		new_offset_vector = ScalingVector(new_offset_vector, micro_step / Absolute(new_offset_vector));
		
		if (atan(new_offset_vector.y / new_offset_vector.x) < 0) {

			this->setAngle(2 * PI + atan(new_offset_vector.y / new_offset_vector.x));
		}
		else {
			this->setAngle(PI + atan(new_offset_vector.y / new_offset_vector.x));
		}


	}
	else new_offset_vector = PolarToDSC(micro_step, this->getAngle());
}


void Ball::checkBricksCollision(vector<Brick*>& BricksList, Vector2f new_offset_vector,
	float micro_step, std::vector<Bonus*>& BonusList, Game& game)
{
	FloatRect ball_bounds = this->getGlobalBounds();
	FloatRect next_ball_bounds = MoveRect(ball_bounds, PolarToDSC(micro_step, this->getAngle()));
	for (Brick* brick : BricksList)
	{
		

		if (next_ball_bounds.intersects(brick->getGlobalBounds()) && brick->getStatus())
		{
			if (!(brick->getHP() == INT32_MAX))
			{
				srand(time(0));
				brick->OnHit(&game.scores);
				if (brick->getHP() == 0)
				{
					brick->changeStatus();
					if (rand() % 1 == 0)
					{
						createbonus(this->getPosition(), BonusList);
					}
				
						
					
				}
				else brick->updateBrick();
			}
			
			if (!game.getAP())
			{
				
				if (atan(new_offset_vector.y / new_offset_vector.x) < 0) this->setAngle(2*PI-atan(new_offset_vector.y / new_offset_vector.x));
				else this->setAngle(PI- atan(new_offset_vector.y / new_offset_vector.x));
			}
			else
			{
				if (brick->getHP() == INT32_MAX) {
					if (atan(new_offset_vector.y / new_offset_vector.x) < 0) this->setAngle(2 * PI - atan(new_offset_vector.y / new_offset_vector.x));
					else this->setAngle(PI - atan(new_offset_vector.y / new_offset_vector.x));
				}
			}
		}
	}
	
}
void Ball::checkBallOut(Game& game)
{
	if (this->getPosition().y >= MAP_END)
	{
		game.removeLife();
		this->setPosition(BALL_INIT_POS);
		this->setAngle(START_ANGLE);
	}
}
void Ball::updateBall(Paddle& paddle, float elapsed_time, Vector2f paddle_offset, std::vector<Brick*>& BricksList, std::vector<Bonus*>& BonusList, Game& game)
{
	FloatRect ball_bounds = this->getGlobalBounds();
	FloatRect paddle_bounds = paddle.getGlobalBounds();
	float micro_step = BALL_SPEED * elapsed_time;
	FloatRect next_ball_bounds = MoveRect(ball_bounds, Vector2f(0.0f, -micro_step));
	Vector2f new_offset_vector = ZERO_VECTOR;
	checkPaddleCollision(paddle_bounds, paddle_offset, new_offset_vector, micro_step);
	checkBallOut(game);
	checkWallCollision(new_offset_vector, micro_step, game);
	checkBricksCollision(BricksList, new_offset_vector, micro_step, BonusList, game);
	this->move(new_offset_vector);
}
