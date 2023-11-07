
#include "brick.h"

float BRICKS_GAP = 5.f;
int32_t ROWS = 3;
int32_t BRICKS_IN_ROW = 10;


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
    this->hp = rand() % 4 + 1;
    
}
void Brick::OnHit(int32_t* scores) {
    *scores += 1;
    decreaseHP();

}
Brick::Brick()
{
    this->setStatus(true);
}
SpeedUp::SpeedUp(Vector2f position) {
    this->setPosition(position);
    this->hp = rand() % 4 + 1;
    this->setTexture(BRICK_TEXTURE_5);
}


void SpeedUp::OnHit(int32_t* scores) {
    *scores += 1;
    decreaseHP();
   BALL_SPEED +=10.f;

}


Unbreakable::Unbreakable(Vector2f position) {
    this->setTexture(BRICK_TEXTURE_5);
    this->setPosition(position);
}

void Brick::updateBrick()
{

    if (this->hp == 1) this->setTexture(BRICK_TEXTURE_1);
    if (this->hp == 2) this->setTexture(BRICK_TEXTURE_2);
    if (this->hp == 3) this->setTexture(BRICK_TEXTURE_3);
    if (this->hp == 4) this->setTexture(BRICK_TEXTURE_4);
    

}

std::vector<Brick*> InitBricksList()
{

    if (!BRICK_TEXTURE_1.loadFromFile("images/brick_1.png") ||
        !BRICK_TEXTURE_2.loadFromFile("images/brick_2.png")
        || !BRICK_TEXTURE_3.loadFromFile("images/brick_3.png")
        || !BRICK_TEXTURE_4.loadFromFile("images/brick_4.png") || !BRICK_TEXTURE_5.loadFromFile("images/brick_5.png"));

    std::vector<Brick*> BricksList;
  
    srand(time(0));
    for (size_t y = 1; y <= ROWS; y+=2)
        for (size_t x = 0; x < BRICKS_IN_ROW; x+=2)
        {

          

           
            int32_t brick_type = rand() % 10;
            if (brick_type < 2) {
                Unbreakable* brick = new Unbreakable(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
                brick->updateBrick();
                BricksList.push_back(brick);
            }
            else if (brick_type > 4) {
                SpeedUp* brick = new SpeedUp(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
                brick->updateBrick();
                BricksList.push_back(brick);
            }
            else {
                Brick* brick = new Brick(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
                brick->updateBrick();
                BricksList.push_back(brick);
            }
          
          
           
        }
    for (size_t y = 0; y <= ROWS; y += 2)
        for (size_t x = 1; x < BRICKS_IN_ROW; x += 2)
        {
            int32_t brick_type = rand() % 10;
            if (brick_type < 2) {
                Unbreakable* brick = new Unbreakable(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
                brick->updateBrick();
                BricksList.push_back(brick);
            }
            else if (brick_type > 4) {
                SpeedUp* brick = new SpeedUp(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
                brick->updateBrick();
                BricksList.push_back(brick);
            }
            else {
                Brick* brick = new Brick(Vector2f(x * (BRICK_SIZE.x + BRICKS_GAP), y * (BRICK_SIZE.y + BRICKS_GAP)));
                brick->updateBrick();
                BricksList.push_back(brick);
            }
        }

    return BricksList;
}

