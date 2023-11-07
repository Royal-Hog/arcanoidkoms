#include "bonus.h"
#include "game.h"
#include <iostream>



void Bonus::setActivated(bool activated)
{
	this->activated = activated;
}
bool Bonus::getActivated()
{
	return this->activated;
}


Bonus::Bonus()
{
		this->setStatus(true);
		this->setActivated(false);
	this->setScale(Vector2f(0.2f, 0.2f));
	Clock clock;
	this->bonus_clock = clock;
}

void Bonus::bonusCollidesPaddle(Paddle& paddle)
{
	FloatRect bonusbounds = this->getGlobalBounds();
	FloatRect paddleBounds = paddle.getGlobalBounds();
	if (bonusbounds.intersects(paddleBounds)) {
		this->setActivated(true);
		this->move(-1000, -1000);
	}
}
void Bonus::bonusMoving(float elapsed_time)
{
	float micro_step = BONUS_SPEED * elapsed_time;
	this->move(Vector2f(0.f, micro_step));
	
}

void Bonus::updateByTime(Game& game)
{
	float elapsed_time = this->bonus_clock.getElapsedTime().asSeconds();
	if (elapsed_time >= 15.f)
	{
		
		this->BonusDeactivate(game);
		this->setStatus(false);
		delete* game.BonusList.begin();
		game.BonusList.erase(game.BonusList.begin());
	}
}



void UpdateBonusList( float elapsed_time,
	 Game& game)
{

	for (auto& bonus : game.BonusList)
	{
		if (bonus->getStatus())
		{
			bonus->bonusCollidesPaddle(game.paddle);
			bonus->bonusMoving(elapsed_time);

			bonus->updateByTime(game);
		}
	}
}




Extrascores::Extrascores(Vector2f position) {
	this->extrascores = 50;
	BONUS_TEXTURE_1.loadFromFile("images/bonus_extrascores.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_1);

}

void Extrascores::Activate(Game& game)
{
	game.addScores(this->extrascores);
}


ReducePaddle::ReducePaddle(Vector2f position)
{
	this->NewSize = sf::Vector2f(0.5f, 1.f);

	BONUS_TEXTURE_2.loadFromFile("images/bonus_redutio.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_2);
}





void ReducePaddle::Activate(Game& game)
{
	game.ChangePaddle(NewSize);

}

void ReducePaddle::BonusDeactivate(Game& game) {
	game.ChangePaddle(Vector2f(1.f,1.f));
}

Extralife::Extralife(Vector2f position)
{
	

	BONUS_TEXTURE_3.loadFromFile("images/bonus_extralife.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_3);
}
void Extralife::Activate(Game& game)
{
	game.addLife();
}



IncreasePaddle::IncreasePaddle(Vector2f position)
{
	this->NewSize = sf::Vector2f(2.f, 1.f);


	BONUS_TEXTURE_4.loadFromFile("images/bonus_engorgio.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_4);
}

void IncreasePaddle::Activate(Game& game)
{
	game.ChangePaddle(NewSize);
}

void IncreasePaddle::BonusDeactivate(Game& game) {
	game.ChangePaddle(Vector2f(1.f, 1.f));
}

Allpervading::Allpervading(Vector2f position)
{
	

	BONUS_TEXTURE_5.loadFromFile("images/bonus_allpervading.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_5);
}

void Allpervading::Activate(Game& game)
{
		game.setAP(true);
}
void Allpervading::BonusDeactivate(Game& game)
{
	game.setBAP(false);
}

IncreaseBallSpeed::IncreaseBallSpeed(Vector2f position)
{
	this->delta_speed = 200.f;

	BONUS_TEXTURE_6.loadFromFile("images/bonus_increase_ball_speed-transformed.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_6);
}

void IncreaseBallSpeed::Activate(Game& game)
{

		
	game.IncreaseSpeed(delta_speed);
	
}

void IncreaseBallSpeed::BonusDeactivate(Game& game)
{
	game.DecreaseSpeed(delta_speed);
}

RandomizeAngle::RandomizeAngle(Vector2f position)
{
	this->rand_angle = ((rand()) % 360) * 3.14 / 360;
	BONUS_TEXTURE_7.loadFromFile("images/bonus_randomize_angle-transformed.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_7);
}

void RandomizeAngle::Activate(Game& game)
{
	game.setRandAngle(rand_angle);
}

BottomAsPaddle::BottomAsPaddle(Vector2f position)
{

	BONUS_TEXTURE_8.loadFromFile("images/bonus_bottom_paddle.png");

	this->setPosition(position);
	this->setTexture(BONUS_TEXTURE_8);
}

void BottomAsPaddle::Activate(Game& game)
{
	game.setBAP(true);
}




void createbonus(Vector2f position, std::vector<Bonus*>& BonusList) {
	//srand(time(0));
	int32_t bonus_type  = rand() % 8 + 1;
	switch (bonus_type) {
	case 1: {
		BonusList.push_back(new Extrascores(position));
		break;
	}
	case 2: {
		BonusList.push_back(new ReducePaddle(position));
		break;
	}
	case 3: {
		BonusList.push_back(new Extralife(position));
		break;
	}
	case 4: {
		BonusList.push_back(new IncreasePaddle(position));
		break;
	}
	case 5: {
		BonusList.push_back(new Allpervading(position));
		break;
	}
	case 6: {
		BonusList.push_back(new IncreaseBallSpeed(position));
		break;
	}
	case 7: {
		BonusList.push_back(new RandomizeAngle(position));
		break;
	}
	case 8: {
		BonusList.push_back(new BottomAsPaddle(position));
		break;
	}
	}
	

}