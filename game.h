#ifndef GAME_H
#define GAME_H
#include "brick.h"
#include "paddle.h"
#include "ball.h"

#include <vector>
class Ball;
class Bonus;
const int32_t WINDOW_HEIGHT = 600;
const int32_t SCORES_FOR_BLOCK = 50;

static sf::Font font;
static sf::Text scores_header;
static sf::Text scores_amount;
static sf::Text level_header;
static sf::Text level_num;
static sf::Text lifes_header;
static sf::Text lifes_amount;

void CheckForWindowClosed(sf::Event& event, sf::RenderWindow& window);




void DrawScene(sf::RenderWindow& window, Ball& ball, Paddle& paddle, std::vector<Brick>& BricksList, std::vector<Bonus*>& BonusList, Game & game);

bool checkCompleteness(std::vector<Brick>& BricksList);


class Game
{
private:
    int32_t level;
    int32_t scores;
    int32_t lifes;
    bool allpervading;
    bool bottom_as_paddle;
public:
    static Game* Play;

    Game();
     ~Game() = default;
    void addScores(int amount);
    void goNextLevel();
    void setBAP(bool BAP);
    bool getBAP();
    void addLife();
    void removeLife();
    void takeOffLife();
    void setAP(bool allpervading);
    bool getAP();
    int32_t getScores();
    int32_t getLifes();
    int32_t getLevelNum();
    void addLevel();
};
void UpdateScene(sf::Clock& clock, Paddle& paddle, Ball& ball,
    std::vector<Brick>& BricksList, std::vector<Bonus*>& BonusList, Game& game);
void initGame(Game& game);
void DrawText(RenderWindow& window, Game& game);
void UpdatePanel(Game& game);
void TextSetter(sf::Text& text, const sf::Font& font, const std::string& stroke, const sf::Vector2f& position);
void LoadFont(Game& game);
void LoadTextures();

#endif