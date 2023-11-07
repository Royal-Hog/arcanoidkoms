#include "game.h"
#include "bonus.h"
#include <iostream>




void Game::addLife()
{
	this->lifes++;
}

void Game::removeLife()
{
	this->lifes--;
}

void Game::IncreaseSpeed(float delta) {
	BALL_SPEED += delta;
}
void Game::DecreaseSpeed(float delta) {
	BALL_SPEED -= delta;
}

void Game::ChangePaddle(Vector2f size) {
	paddle.setScale(size);
}

void Game::setAP(bool AP) {
	ball.allpervading = AP;
}
void Game::setBAP(bool BAP) {
	ball.bottom_as_paddle = BAP;
}
void Game::setRandAngle(float rand) {
	ball.angle = rand;
}

void Game::addLevel()
{
	this->level++;
}

void Game::TextSetter(sf::Text& text,const sf::Font& font, const std::string& stroke, const sf::Vector2f& position)
{
	text.setFont(font);
	text.setCharacterSize(20);
	text.setFillColor(sf::Color::White);
	text.setString(stroke);
	text.setPosition(position);
}

void Game::UpdatePanel()
{

	

	std::string my_scores_panel = "Scores: ";
	std::string my_scores_amount = std::to_string(scores);
	std::string my_lifes_panel = "Lifes: ";
	std::string my_lifes_amount = std::to_string(lifes);
	std::string my_level_panel = "Level: ";
	std::string my_level_num = std::to_string(level);
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


void Game::DrawText(RenderWindow& window)
{
	window.draw(level_header);
	window.draw(level_num);
	window.draw(lifes_header);
	window.draw(lifes_amount);
	window.draw(scores_header);
	window.draw(scores_amount);
}



void Game::DrawBricks(RenderWindow& window)
{
	for (Brick* brick : BricksList) if (brick->getStatus()) window.draw(*brick);
}
void Game::CheckForWindowClosed(sf::Event& event, sf::RenderWindow& window)
{
	while (window.pollEvent(event))
		if (event.type == sf::Event::Closed) window.close();
}
void Game::BonusProcess()
{
	for (auto bonus : BonusList)
	{
		if (bonus->getActivated())
		{
			bonus->Activate(*this);
			bonus->setActivated(false);
			
		}
	}
}

void Game::UpdateScene()
{
	float elapsed_time = clock.getElapsedTime().asSeconds();
	clock.restart();
	paddle.updateDirection();
	ball.updateBall( elapsed_time, *this);
	UpdateBonusList(elapsed_time, *this);
	BonusProcess();
}

void Game::DrawBonuses(RenderWindow& window)
{
	for (auto& bonus : BonusList) if (bonus->getStatus() && !bonus->getActivated()) window.draw(*bonus);
}
void Game::DrawScene(sf::RenderWindow& window)
{
	window.clear();
	window.draw(paddle);
	window.draw(ball);
	DrawBricks(window);
	DrawText(window);
	if (ball.bottom_as_paddle)
	{
		sf::RectangleShape bottom_line;
		bottom_line.setSize(Vector2f(WINDOW_WIDTH, 4.f));
		bottom_line.setPosition(Vector2f(0,590));
		bottom_line.setFillColor(Color::White);
		window.draw(bottom_line);
	}
	DrawBonuses(window);
	window.display();
}

bool Game::checkCompleteness()
{
	bool level_complete = true;
	for (Brick* brick : BricksList)
		if (brick->getStatus() && (brick->getHP() >=0)) 
			level_complete = false;
	
	if (level_complete) addLevel();
	return level_complete;
}

bool checkDefeat(int32_t lifes)
{
	if (lifes == 0) { 
		return true; }

	else return false;
}

void Game::LoadTextures()
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
    //paddle = Paddle(PADDLE_TEXTURE);
	this->level = 1;
	this->scores = 0;
	this->lifes = 2;
	
}

void Game::addScores(int amount)
{
	this->scores += amount;
}

void Game::goNextLevel()
{
	this->level++;
}

void Game::LoadFont()
{
	if (!font.loadFromFile("fonts/ARIAL.ttf"))
	{
		std::cerr << "Failed font loading" << std::endl;
		return;
	}
}

void Game::gameloop(RenderWindow& window) {
	while (window.isOpen())
	{
		sf::Event event;
		UpdatePanel();
	
		CheckForWindowClosed(event, window);
		UpdateScene();
		DrawScene(window);
		if (checkCompleteness()) { ROWS++; BricksList = InitBricksList(); }
		if (checkDefeat(lifes)) window.close();
	}
}

void Game::initGame()
{

	
	RenderWindow window(sf::VideoMode(WINDOW_WIDTH , WINDOW_HEIGHT+300.f), "Arcanoid");
	LoadTextures();
	LoadFont();
	paddle = Paddle(PADDLE_TEXTURE);
	ball = Ball(BALL_TEXTURE);
	 BricksList = InitBricksList();
	gameloop(window);
	for (auto bonus : BonusList) delete bonus;
	for (auto brick : BricksList) delete brick;
	BonusList.clear();
	BricksList.clear();
}