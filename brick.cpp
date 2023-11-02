
#include "brick.h"

float BRICKS_GAP = 5.f;
int32_t ROWS = 3;
int32_t BRICKS_IN_ROW = 10;

void Brick::setHP(int32_t hp)
{
    this->hp = hp;
}
int32_t Brick::getHP()
{
    return this->hp;
}
void Brick::decreaseHP()
{
    this->hp--;
}
Brick::Brick(Vector2f position)
{
    this->setPosition(position);
    this->setStatus(true);
    this->hp = rand() % 5 + 1;
    if (this->hp == 5)
        this->hp = INT32_MAX;
}

void Brick::updateBrick()
{
  
    if (this->hp == 1) this->setTexture(BRICK_TEXTURE_1);
    if (this->hp == 2) this->setTexture(BRICK_TEXTURE_2);
    if (this->hp == 3) this->setTexture(BRICK_TEXTURE_3);
    if (this->hp == 4) this->setTexture(BRICK_TEXTURE_4);
    if (this->hp == INT32_MAX) this->setTexture(BRICK_TEXTURE_5);
}

std::vector<Brick> InitBricksList()
{

    if (!BRICK_TEXTURE_1.loadFromFile("images/brick_1.png") ||
        !BRICK_TEXTURE_2.loadFromFile("images/brick_2.png")
        || !BRICK_TEXTURE_3.loadFromFile("images/brick_3.png")
        || !BRICK_TEXTURE_4.loadFromFile("images/brick_4.png")
        || !BRICK_TEXTURE_5.loadFromFile("images/brick_5.png"));

    std::vector<Brick> BricksList;
    float iterator_x = FIRST_BRICK_POS.x;
    float iterator_y = FIRST_BRICK_POS.y;
    /*for (size_t y = 1; y <= ROWS; y++)
        for (size_t x = 0; x < BRICKS_IN_ROW; x++)
        {
            Brick brick = Brick(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
            brick.updateBrick();
            BricksList.push_back(brick);
        }*/
    for (size_t y = 1; y <= ROWS; y+=2)
        for (size_t x = 0; x < BRICKS_IN_ROW; x+=2)
        {
            Brick brick = Brick(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
            brick.updateBrick();
            BricksList.push_back(brick);
        }
    for (size_t y = 0; y <= ROWS; y += 2)
        for (size_t x = 1; x < BRICKS_IN_ROW; x += 2)
        {
            Brick brick = Brick(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
            brick.updateBrick();
            BricksList.push_back(brick);
        }

    return BricksList;
}

void DrawBricks(RenderWindow& window, std::vector<Brick>& BricksList)
{
    for (Brick& brick : BricksList) if (brick.getStatus()) window.draw(brick);
}