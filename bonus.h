#ifndef BONUS_H
#define BONUS_H
#include "entity.h"
#include <random>
class Game;
class Ball;
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
	virtual void Activate(Game& game, Paddle& paddle, Ball& ball) {};
	virtual void ActivateNew(){};
	virtual void BonusDeactivate(Game& game, Paddle& paddle) {};
	void bonusCollidesPaddle(Paddle& paddle);
	void bonusMoving(float elapsed_time);
	virtual ~Bonus() = default;
	void updateByTime(Game& game, Ball& ball, Paddle& paddle, std::vector<Bonus*>& BonusList);
};

void UpdateBonusList(std::vector<Bonus*>& BonusList, float elapsed_time,
	Paddle& paddle, Game& game, Ball& ball);

void DrawBonuses(RenderWindow& window, std::vector<Bonus*>& BonusList);


class Extrascores : public Bonus
{
private:
	int32_t extrascores;
	//int32_t* scores;
public:

	Extrascores(Vector2f position);
	//void ActivateNew() override;
	 void Activate(Game& game, Paddle& paddle, Ball& ball) override;
	  ~Extrascores() override = default;
};

class ReducePaddle : public Bonus
{
private:
	sf::Vector2f NewSize;
	//Paddle* paddle;
public:
	ReducePaddle(Vector2f position);
	//void ActivateNew() override;
	void Activate(Game& game, Paddle& paddle, Ball& ball) override;
	void BonusDeactivate(Game& game, Paddle& paddle) override;
	 ~ReducePaddle() override = default;
};

class Extralife : public Bonus
{
public:
	Extralife(Vector2f position);
	void Activate(Game& game, Paddle& paddle, Ball& ball) override;
	~Extralife() override = default;
private:
};

class IncreasePaddle : public Bonus
{
private:
	sf::Vector2f NewSize = sf::Vector2f(2.f, 1.f);
public:
	IncreasePaddle(Vector2f position);
	void Activate(Game& game, Paddle& paddle, Ball& ball) override;
	void BonusDeactivate(Game& game, Paddle& paddle) override;
	 ~IncreasePaddle() override = default;
};


class Allpervading : public Bonus
{
private:
public:
	Allpervading(Vector2f position);
	void Activate(Game& game, Paddle& paddle, Ball& ball) override;
	void BonusDeactivate(Game& game, Paddle& paddle) override;
	 ~Allpervading() override = default;
};


class IncreaseBallSpeed : public Bonus
{
private:
	float delta_speed;
public:
	IncreaseBallSpeed(Vector2f position);
	void Activate(Game& game, Paddle& paddle, Ball& ball) override;
	void BonusDeactivate(Game& game, Paddle& paddle) override;
	 ~IncreaseBallSpeed() override = default;
};
class RandomizeAngle : public Bonus
{
private:
	float rand_angle;
public:
	RandomizeAngle(Vector2f position);
	void Activate(Game& game, Paddle& paddle, Ball& ball) override;

	 ~RandomizeAngle() override = default;
};

class BottomAsPaddle : public Bonus
{
private:
public:
	BottomAsPaddle(Vector2f position);
	void Activate(Game& game, Paddle& paddle,Ball& ball) override;
	void BonusDeactivate(Game& game, Paddle& paddle) override;
	 ~BottomAsPaddle() override = default;
};

void createbonus(Vector2f position, std::vector<Bonus*>& BonusList/*, int32_t* scores, Paddle* paddle*/);
#endif