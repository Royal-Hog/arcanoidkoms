#ifndef ENTITY_H
#define ENTITY_H
#include <SFML/Graphics.hpp>
using namespace sf;
static Texture BALL_TEXTURE;
static Texture PADDLE_TEXTURE;
static Texture BRICK_TEXTURE_1;
static Texture BRICK_TEXTURE_2;
static Texture BRICK_TEXTURE_3;
static Texture BRICK_TEXTURE_4;
static Texture BRICK_TEXTURE_5;

static Texture BONUS_TEXTURE_1;
static Texture BONUS_TEXTURE_2;
static Texture BONUS_TEXTURE_3;
static Texture BONUS_TEXTURE_4;
static Texture BONUS_TEXTURE_5;
static Texture BONUS_TEXTURE_6;
static Texture BONUS_TEXTURE_7;
static Texture BONUS_TEXTURE_8;




extern Vector2f PADDLE_INIT_POS;
extern float PADDLE_SPEED;

extern Vector2f BALL_INIT_POS;
extern Vector2f BALL_SCALE;
extern float BALL_SPEED;

extern Vector2f FIRST_BRICK_POS;
extern Vector2f BRICK_SIZE;

class Entity : public Sprite
{
public:
	bool Colliding(FloatRect& rect);
	void setStatus(bool status);
	void changeStatus();
	bool getStatus();
	virtual ~Entity() = default;
private:
	bool is_existing;
};

static const sf::FloatRect MoveRect(const sf::FloatRect& my_rect, sf::Vector2f offset)
{
	return { my_rect.left + offset.x, my_rect.top + offset.y, my_rect.width, my_rect.height };
}
#endif