#include "Player.h"

using namespace sf;

int ground = 875;

const int H = 16;
const int W = 32;

float offsetX = 0, offsetY = 0;

extern String TileMap[H];

Player::Player(Texture& image)
{
	sprite.setTexture(image);
	sprite.setTextureRect(IntRect(10, 85, 75, 88));

	rect = FloatRect(10, 85, 75, 88);
	rect.top = 875;
	rect.left = 100;

	dx = dy = 0;

	currentFrame = 0;
}

void Player::update(float time)
{
	rect.left += dx * time;
	Collision(0);

	if (!onGround)
		dy = dy + 0.0002 * time;

	rect.top += dy * time;
	
	onGround = false;

	Collision(1);
	//if (rect.top > ground)
	//{
	//	rect.top = ground;
	//	dy = 0;
	//	onGround = true;
	//}

	currentFrame += 0.005 * time;
	if (currentFrame > 6)
		currentFrame -= 6;

	if (dx < 0)
		sprite.setTextureRect(IntRect(10 + 85 * int(currentFrame) + 75, 85, -75, 88));
	if (dx > 0)
		sprite.setTextureRect(IntRect(10 + 85 * int(currentFrame), 85, 75, 88));

	sprite.setPosition(rect.left - offsetX, rect.top - offsetY);

	dx = 0;
}

void Player::Collision(int dir)
{
	for (int i = rect.top / 64; i < (rect.top + rect.height) / 64; i++)
		for (int j = rect.left / 64; j < (rect.left + rect.width) / 64; j++)
		{
			if (TileMap[i][j] == 'B')
			{
				if (dx > 0 && dir == 0)
					rect.left = j * 64 - rect.width;
				if (dx < 0 && dir == 0)
					rect.left = j * 64 + 64;

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

			if (TileMap[i][j] == '0')
			{
				TileMap[i][j] = ' ';
			}
		}
}