#ifndef GAME_H
#define GAME_H
#include "brick.h"
#include "paddle.h"
#include "ball.h"

#include <vector>
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



class Game
{
private:
    int32_t level;
    
    int32_t lifes;
    

    void BonusProcess();
    void DrawScene(sf::RenderWindow& window);
    void DrawBricks(RenderWindow& window);
    void DrawBonuses(RenderWindow& window);

    void CheckForWindowClosed(sf::Event& event, sf::RenderWindow& window);
    bool checkCompleteness();
    void UpdateScene();
    void DrawText(RenderWindow& window);
    void UpdatePanel();
    void TextSetter(sf::Text& text, const sf::Font& font, const std::string& stroke, const sf::Vector2f& position);
    void LoadFont();
    void LoadTextures();
    void gameloop(RenderWindow& window);
  
public:

    Paddle paddle;
    Ball ball;
    Clock clock;
    std::vector<Brick*> BricksList;
    std::vector<Bonus*> BonusList;
    int32_t scores;
    Game();
     ~Game() = default;
     void setAP(bool AP);
     void setBAP(bool BAP);
     void setRandAngle(float rangle);
     void ChangePaddle(sf::Vector2f size);
    void addScores(int amount);
    void goNextLevel();
    void addLife();
    void removeLife();

    void addLevel();
    void initGame();
    void IncreaseSpeed(float delta);
    void DecreaseSpeed(float delta);
    
};



#endif