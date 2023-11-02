#ifndef BALL_H
#define BALL_H
#include "entity.h"

#include "vector_extra_func.h"
#define PI 3.14159265358979323846
const int32_t WINDOW_WIDTH = 800;
class Brick;
class Paddle;
class Bonus;
class Game;
class Ball : public Entity
{
public:
	void setAngle(float angle);
	float getAngle();
	Ball(Texture& texture);
    ~Ball() override = default;
	void checkWallCollision(Vector2f& new_offset_vector, float micro_step, Game& game);
	void checkPaddleCollision(FloatRect& paddle_bounds, Vector2f paddle_offset, Vector2f& new_offset_vector, float micro_step);
	void checkBricksCollision(vector<Brick>& BricksList, Vector2f new_offset_vector, float micro_step, std::vector<Bonus*>& BonusList, Game& game);
	void checkBallOut(Game& game);
	void updateBall(Paddle& paddle, float elapsed_time, Vector2f paddle_offset, std::vector<Brick>& BricksList, std::vector<Bonus*>& BonusList, Game& game);
private:
	float angle;
};

#endif