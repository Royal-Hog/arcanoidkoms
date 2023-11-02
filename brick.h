#ifndef BRICK_H
#define BRICK_H
#include "entity.h"
#include <random>

extern float BRICKS_GAP;
extern int32_t ROWS;
extern int32_t BRICKS_IN_ROW;

class Brick : public Entity
{
public:
	void setHP(int32_t hp);
	int32_t getHP();
	void decreaseHP();
	Brick(Vector2f position);
	 ~Brick() override = default;
	void updateBrick();
private:
	int32_t hp;
};

std::vector<Brick> InitBricksList();

void DrawBricks(RenderWindow& window, std::vector<Brick>& BricksList);
#endif