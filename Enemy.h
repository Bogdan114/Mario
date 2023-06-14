#pragma once
#include<SFML/Graphics.hpp>

class Enemy
{
public:

	void set(sf::Texture& image);
	void update(float time);
	void Collision(int dir);

	float dx, dy;
	sf::FloatRect rect;
	bool onGround;
	sf::Sprite sprite;
	float currentFrame;
	bool life;

	bool left;
};

