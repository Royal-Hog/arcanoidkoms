#ifndef BONUS_H
#define BONUS_H
#include "entity.h"
#include <random>
class Game;
class Paddle;



const float BONUS_SPEED = 100.f;
class Bonus : public Entity
{
private:
	

	bool activated;
public:
    Clock bonus_clock;
	
	
	void setActivated(bool activated);
	bool getActivated();
	Bonus();
	virtual void Activate(Game& game) {};
	virtual void BonusDeactivate(Game& game) {};
	void bonusCollidesPaddle(Paddle& paddle);
	void bonusMoving(float elapsed_time);
	virtual ~Bonus() = default;
	void updateByTime(Game& game);
};

void UpdateBonusList(float elapsed_time, Game& game);




class Extrascores : public Bonus
{
private:
	int32_t extrascores;

public:

	Extrascores(Vector2f position);
	 void Activate(Game& game) override;
	  ~Extrascores() override = default;
};

class ReducePaddle : public Bonus
{
private:
	sf::Vector2f NewSize;
public:
	ReducePaddle(Vector2f position);
	void Activate(Game& game) override;
	void BonusDeactivate(Game& game) override;
	 ~ReducePaddle() override = default;
};

class Extralife : public Bonus
{
public:
	Extralife(Vector2f position);
	void Activate(Game& game) override;
	~Extralife() override = default;
private:
};

class IncreasePaddle : public Bonus
{
private:
	sf::Vector2f NewSize = sf::Vector2f(2.f, 1.f);
public:
	IncreasePaddle(Vector2f position);
	void Activate(Game& game) override;
	void BonusDeactivate(Game& game) override;
	 ~IncreasePaddle() override = default;
};


class Allpervading : public Bonus
{
private:
public:
	Allpervading(Vector2f position);
	void Activate(Game& game) override;
	void BonusDeactivate(Game& game) override;
	 ~Allpervading() override = default;
};


class IncreaseBallSpeed : public Bonus
{
private:
	float delta_speed;
public:
	IncreaseBallSpeed(Vector2f position);
	void Activate(Game& game) override;
	void BonusDeactivate(Game& game) override;
	 ~IncreaseBallSpeed() override = default;
};
class RandomizeAngle : public Bonus
{
private:
	float rand_angle;
public:
	RandomizeAngle(Vector2f position);
	void Activate(Game& game) override;

	 ~RandomizeAngle() override = default;
};

class BottomAsPaddle : public Bonus
{
private:
public:
	BottomAsPaddle(Vector2f position);
	void Activate(Game& game) override;
	
	 ~BottomAsPaddle() override = default;
};

void createbonus(Vector2f position, std::vector<Bonus*>& BonusList);
#endif