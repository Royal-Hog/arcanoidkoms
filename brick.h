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
	
	int32_t getHP();
	void decreaseHP();
	 Brick();
     Brick(Vector2f position);
	 ~Brick() override = default;
	void updateBrick();
	virtual void OnHit(int32_t* scores);
	int32_t hp;
private:
	
};

class Unbreakable :public Brick
{
public:
	Unbreakable(Vector2f position);
	void OnHit(int32_t* scores) override {}


};

class SpeedUp :public Brick {

public:
	SpeedUp(Vector2f position);
	void OnHit(int32_t* scores) override;
};


std::vector<Brick*> InitBricksList();

#endif