#include "Enemy.h"

using namespace sf;

extern float offsetX, offsetY;
const int H = 16;
const int W = 32;
extern String TileMap[H];

void Enemy::set(sf::Texture& image)
{
	sprite.setTexture(image);
	sprite.setTextureRect(IntRect(10, 85, 75, 88));
	rect = FloatRect(10, 85, 75, 88);

	rect.top = 800;
	rect.left =700;

	left = false;

	dx = 0.05;
	currentFrame = 0;
	life = true;
}

void Enemy::update(float time)
{
	if (left)
		rect.left += dx * time;
	else
		rect.left -= dx * time;
	Collision(0);

	currentFrame += time * 0.005;
	if (currentFrame > 2)
		currentFrame -= 2;

	//if (dx < 0)
	//	sprite.setTextureRect(IntRect(10 + 85 * int(currentFrame) + 75, 85, -75, 88));
	//if (dx > 0)
	//	sprite.setTextureRect(IntRect(10 + 85 * int(currentFrame), 85, 75, 88));

	if (!life)
		sprite.setColor(Color::Blue);

	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);
}

void Enemy::Collision(int dir)
{
	for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
		for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
		{
			if (TileMap[i][j] == 'B')
			{
				if (dx > 0 && dir == 0)
				{
					left = false;
					rect.left = j * 64 - rect.width;
				}
				if (dx < 0 && dir == 0)
				{
					left = true;
					rect.left = j * 64 + 64;
				}
				if (dy > 0 && dir == 1)
				{
					rect.top = i * 64 - rect.height;
					dy = 0;
					onGround = true;
				}
				if (dy < 0 && dir == 1)
				{
					rect.top = i * 64 + 64;
					dy = 0;
				}
			}
		}
}