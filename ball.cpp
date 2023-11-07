#include "ball.h"
#include "game.h"

#include <iostream>




Ball::Ball(Texture& texture)
{
	this->setPosition(BALL_INIT_POS);
	this->angle=START_ANGLE;
	this->setStatus(true);
	this->setTexture(texture);
	this->setScale(BALL_SCALE);
	this->allpervading = false;
	this->bottom_as_paddle = false;
}
void Ball::checkWallCollision(Vector2f& new_offset_vector, float micro_step, Game& game)
{
	if (this->getPosition().y <= 0)
	{
		angle=-angle;
		new_offset_vector = PolarToDSC(micro_step, angle);
	}
	if (this->getPosition().x <= 5 || this->getPosition().x >= WINDOW_WIDTH-10)
	{
		angle=PI - angle;
		new_offset_vector = PolarToDSC(micro_step, angle);
	}

	if (bottom_as_paddle && this->getPosition().y >= MAP_BOTTOM)
	{
		if (atan(new_offset_vector.y / new_offset_vector.x) < 0) {

			angle = (PI - atan(new_offset_vector.y / new_offset_vector.x));
		}
		else {
			angle = (2 * PI - atan(new_offset_vector.y / new_offset_vector.x));
		}
		bottom_as_paddle = false;
	}
}
void Ball::checkPaddleCollision(FloatRect& paddle_bounds, Vector2f paddle_offset, Vector2f& new_offset_vector, float micro_step)
{
	FloatRect ball_bounds = this->getGlobalBounds();
	FloatRect next_ball_bounds = MoveRect(ball_bounds, PolarToDSC(2*micro_step, angle));

	if (next_ball_bounds.intersects(paddle_bounds))
	{
		Vector2f ball_offset = PolarToDSC(micro_step, angle);
		new_offset_vector = VectorSum(ball_offset, ball_offset);
		new_offset_vector = VectorSum(new_offset_vector, paddle_offset);
		new_offset_vector = ScalingVector(new_offset_vector, micro_step / Absolute(new_offset_vector));
		
		if (abs(this->getPosition().y - 550 )> 10) {
			if (atan(new_offset_vector.y / new_offset_vector.x) < 0) {

				angle = ( PI - atan(new_offset_vector.y / new_offset_vector.x));
			}
			else {
				angle = (2*PI - atan(new_offset_vector.y / new_offset_vector.x));
			}
		}
	

	}
	else new_offset_vector = PolarToDSC(micro_step, angle);
}


void Ball::checkBricksCollision( Vector2f new_offset_vector,
	float micro_step, Game& game)
{
	FloatRect ball_bounds = this->getGlobalBounds();
	FloatRect next_ball_bounds = MoveRect(ball_bounds, PolarToDSC(2*micro_step, angle));
	for (Brick* brick : game.BricksList)
	{


		if (next_ball_bounds.intersects(brick->getGlobalBounds()) && brick->getStatus())
		{

			srand(time(0));
			brick->OnHit(&game.scores);
			if (brick->getHP() == 0)
			{
				brick->changeStatus();
				if (rand() % 2 == 1)
				{
					createbonus(this->getPosition(), game.BonusList);
				}



			}
			else brick->updateBrick();


			if (!allpervading|| !(brick->getHP() >= 0))
			{


				if (abs(this->getPosition().y - brick->getPosition().y) > 16) {
					if (new_offset_vector.y < 0) {
						if (atan(new_offset_vector.y / new_offset_vector.x) < 0) angle=(2 * PI - atan(new_offset_vector.y / new_offset_vector.x));
						else angle=(PI - atan(new_offset_vector.y / new_offset_vector.x));
					}
					else {
						
						if (atan(new_offset_vector.y / new_offset_vector.x) < 0) {

							angle = (PI-  atan(new_offset_vector.y / new_offset_vector.x));
						}
						else {
							angle = (2*PI - atan(new_offset_vector.y / new_offset_vector.x));
						}
					}
				}
				else {
					
					if (new_offset_vector.y < 0) {
					
						if (atan(new_offset_vector.y / new_offset_vector.x) < 0) angle=(  PI- atan(new_offset_vector.y / new_offset_vector.x));
						else angle=( 2*PI- atan(new_offset_vector.y / new_offset_vector.x));
					}
					else {
						if (atan(new_offset_vector.y / new_offset_vector.x) < 0) {

							angle=( 2*PI- atan(new_offset_vector.y / new_offset_vector.x));
						}
						else {
							angle=(PI- atan(new_offset_vector.y / new_offset_vector.x));
						}
					}
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
		angle=START_ANGLE;
	}
}
void Ball::updateBall( float elapsed_time, Game& game)
{
	FloatRect ball_bounds = this->getGlobalBounds();
	FloatRect paddle_bounds = game.paddle.getGlobalBounds();
	float micro_step = BALL_SPEED * elapsed_time;
	FloatRect next_ball_bounds = MoveRect(ball_bounds, Vector2f(0.0f, -micro_step));
	Vector2f new_offset_vector = ZERO_VECTOR;
	checkPaddleCollision(paddle_bounds, game.paddle.updatePaddle(elapsed_time), new_offset_vector, micro_step);
	checkBallOut(game);
	checkWallCollision(new_offset_vector, micro_step, game);
	checkBricksCollision( new_offset_vector, micro_step, game);
	this->move(new_offset_vector);
}
