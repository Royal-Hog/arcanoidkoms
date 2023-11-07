#ifndef BALL_H
#define BALL_H
#include "entity.h"
#include "bonus.h"

#include "vector_extra_func.h"

const int32_t WINDOW_WIDTH = 800;

class Game;
class Ball : public Entity
{
public:
	bool bottom_as_paddle;
	bool allpervading;
	Ball(Texture& texture);
	Ball(){}
    ~Ball() override = default;
	
	void updateBall( float elapsed_time, Game& game);
	float angle;
private:
	void checkWallCollision(Vector2f& new_offset_vector, float micro_step, Game& game);
	void checkPaddleCollision(FloatRect& paddle_bounds, Vector2f paddle_offset, Vector2f& new_offset_vector, float micro_step);
	void checkBricksCollision(Vector2f new_offset_vector, float micro_step, Game& game);
	void checkBallOut(Game& game);
};

#endif