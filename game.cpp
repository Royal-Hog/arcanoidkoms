#include "game.h"
#include "ball.h"
#include "bonus.h"
#include <iostream>



void Game::setBAP(bool BAP)
{
	this->bottom_as_paddle = BAP;
}

bool Game::getBAP()
{
	return this->bottom_as_paddle;
}

void Game::addLife()
{
	this->lifes++;
}

void Game::removeLife()
{
	this->lifes--;
}

void Game::takeOffLife()
{
	if (!this->lifes == 0)
		this->lifes--;
}

void Game::setAP(bool allpervading)
{
	this->allpervading = allpervading;
}

bool Game::getAP()
{
	return this->allpervading;
}

int32_t Game::getScores()
{
	return this->scores;
}

int32_t Game::getLifes()
{
	return this->lifes;
}

int32_t Game::getLevelNum()
{
	return this->level;
}

void Game::addLevel()
{
	this->level++;
}

void TextSetter(sf::Text& text,const sf::Font& font, const std::string& stroke, const sf::Vector2f& position)
{
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setString(stroke);
	text.setPosition(position);
}

void UpdatePanel(Game& game)
{

	

	std::string my_scores_panel = "Scores: ";
	std::string my_scores_amount = std::to_string(game.getScores());
	std::string my_lifes_panel = "Lifes: ";
	std::string my_lifes_amount = std::to_string(game.getLifes());
	std::string my_level_panel = "Level: ";
	std::string my_level_num = std::to_string(game.getLevelNum());
	Vector2f v1 = Vector2f(60, 650);
	Vector2f v2 = Vector2f(130, 650);
	Vector2f v3 = Vector2f(60, 725);
	Vector2f v4 = Vector2f(130, 725);
	Vector2f v5 = Vector2f(60, 800);
	Vector2f v6 = Vector2f(130, 800);
	TextSetter(scores_header, font, my_scores_panel, v1);
	TextSetter(scores_amount, font, my_scores_amount, v2);
	TextSetter(lifes_header, font, my_lifes_panel, v3);
	TextSetter(lifes_amount, font, my_lifes_amount, v4);
	TextSetter(level_header, font, my_level_panel, v5);
	TextSetter(level_num, font, my_level_num, v6);
}


void DrawText(RenderWindow& window, Game& game)
{
	window.draw(level_header);
	window.draw(level_num);
	window.draw(lifes_header);
	window.draw(lifes_amount);
	window.draw(scores_header);
	window.draw(scores_amount);
}


void CheckForWindowClosed(sf::Event& event, sf::RenderWindow& window)
{
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed) window.close();
}
void BonusProcess(std::vector<Bonus*>& BonusList, Game& game, Paddle& paddle, Ball& ball)
{
	for (auto bonus : BonusList)
	{
		if (bonus->getActivated())
		{

			bonus->Activate(game,paddle, ball);
			bonus->setActivated(false);
			//запомнить указатель на этот бонус, удалить его из массива(errase) удалить запомненный указатель(delete) виртуальный диструктр внутри бонуса 
			/*if (bonus.getBonusType() == BonusType::ALLPERVADING)
			{
				game.setAP(true);
				bonus.setActivated(false);
			}
			
			if (bonus.getBonusType() == BonusType::EXTRALIFE)
			{
				game.addLife();
				bonus.setActivated(false);
			}
			if (bonus.getBonusType() == BonusType::EXTRASCORES)
			{
				game.addScores(50);
				bonus.setActivated(false);
			}
			if (bonus.getBonusType() == BonusType::INCREASE_PADDLE)
			{
				paddle.setScale(Vector2f(2.f, 1.f));
				bonus.setActivated(false);
			}
			if (bonus.getBonusType() == BonusType::REDUCE_PADDLE)
			{
				paddle.setScale(Vector2f(0.5f, 1.f));
				bonus.setActivated(false);
			}
			if (bonus.getBonusType() == BonusType::BOTTOM_AS_PADDLE)
			{
				bonus.setActivated(false);
				game.setBAP(true);
			}
			if (bonus.getBonusType() == BonusType::RANDOMIZE_ANGLE)
			{
				ball.setAngle(static_cast<float>((rand() % 360)) * 0.0175f);
				bonus.setActivated(false);
			}
			if (bonus.getBonusType() == BonusType::INCREASE_BALL_SPEED)
			{
				bonus.setActivated(false);
				BALL_SPEED += 250.f;

			}*/
		}
	}
}

void UpdateScene(sf::Clock& clock, Paddle& paddle, Ball& ball,
	std::vector<Brick>& BricksList, std::vector<Bonus*>& BonusList, Game& game)
{
	float elapsed_time = clock.getElapsedTime().asSeconds();
	clock.restart();
	paddle.updateDirection();
	ball.updateBall(paddle, elapsed_time,
		paddle.updatePaddle(elapsed_time), BricksList, BonusList, game);
	UpdateBonusList(BonusList, elapsed_time, paddle, game, ball);
	BonusProcess(BonusList, game, paddle, ball);
}
void DrawScene(sf::RenderWindow& window, Ball& ball, Paddle& paddle, std::vector<Brick>& BricksList, std::vector<Bonus*>& BonusList,Game& game)
{
	window.clear();
	window.draw(paddle);
	window.draw(ball);
	DrawBricks(window, BricksList);
	DrawText(window, game);
	if (game.getBAP())
	{
		sf::RectangleShape bottom_line;
		bottom_line.setSize(Vector2f(WINDOW_WIDTH, 4.f));
		bottom_line.setPosition(Vector2f(0,590));
		bottom_line.setFillColor(Color::White);
		window.draw(bottom_line);
	}
	DrawBonuses(window, BonusList);
	window.display();
}

bool checkCompleteness(std::vector<Brick>& BricksList, Game& game)
{
	bool level_complete = true;
	for (Brick& brick : BricksList)
		if (brick.getStatus() && !(brick.getHP() == INT32_MAX)) 
			level_complete = false;
	
	if (level_complete) game.addLevel();
	return level_complete;
}

bool checkDefeat(int32_t lifes)
{
	if (lifes == 0) { 
		return true; }

	else return false;
}

void LoadTextures()
{
	if (!BALL_TEXTURE.loadFromFile("images/ball_tmp-transformed.png")
		|| !PADDLE_TEXTURE.loadFromFile("images/paddle_texture.png"))
	{
		std::cerr << "Unable to load file . . ." << std::endl;
		return;
	}
}



Game::Game()
{
	this->level = 1;
	this->scores = 0;
	this->lifes = 2;
	this->allpervading = false;
	this->bottom_as_paddle = false;
}

void Game::addScores(int amount)
{
	this->scores += amount;
}

void Game::goNextLevel()
{
	this->level++;
}

void LoadFont(Game& game)
{
	if (!font.loadFromFile("fonts/ARIAL.ttf"))
	{
		std::cerr << "Failed font loading" << std::endl;
		return;
	}
}



void initGame(Game& game)
{

	
	RenderWindow window(sf::VideoMode(WINDOW_WIDTH , WINDOW_HEIGHT+300.f), "Arcanoid");
	LoadTextures();
	LoadFont(game);
	Paddle paddle = Paddle(PADDLE_TEXTURE);
	Ball ball = Ball(BALL_TEXTURE);
	Clock clock;
	std::vector<Brick> BricksList = InitBricksList();
	std::vector<Bonus*> BonusList;
	UpdatePanel(game);
	while (window.isOpen())
	{
		sf::Event event;
		UpdatePanel(game);
		DrawText(window, game);
		CheckForWindowClosed(event, window);
		UpdateScene(clock, paddle, ball, BricksList, BonusList, game);
		DrawScene(window, ball, paddle, BricksList, BonusList,game);
		if (checkCompleteness(BricksList,game)) { ROWS++; BricksList = InitBricksList(); }
		if (checkDefeat(game.getLifes())) window.close();
	}
}