#include<SFML/Graphics.hpp>

#include "Player.h"
#include "Enemy.h"

using namespace sf;

//Rect (x, y, width, height)
// Texture
// Sprite

const int H = 16;
const int W = 32;
extern float offsetX, offsetY;

String TileMap[H] = {
	"BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB",
	"B                    B       BB",
	"B                    B       BB",
	"B                    B       BB",
	"B                    B   0   BB",
	"B                    B       BB",
	"B    000             B       BB",
	"B                    BB      BB",
	"B                            BB",
	"B    BBB                   BBBB",
	"B                            BB",
	"B                            BB",
	"B                            BB",
	"B                            BB",
	"B                            BB",
	"BBBBB    BBBBBBBBBBBBBBBBBBBBBB",
};

int main()
{
	RenderWindow window(VideoMode(2048, 1024), "Test!"); // Создаём окно с названием Test
	//CircleShape MyCircle(100.f); // Окружность радиусом 100
	//MyCircle.setFillColor(Color::Green); // Задаём цвет зелёный

	Texture t;
	t.loadFromFile("mario.png");
	Texture bonus;
	bonus.loadFromFile("tileset.png");

	float currentFrame = 0;

	Player p(t);
	//Enemy enemy;
	//enemy.set(t);

	Clock clock;

	RectangleShape rectangle;
	rectangle.setSize(Vector2f(64, 64));
	rectangle.setTexture(&bonus);

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();

		time = time / 300;

		Event event;
		while (window.pollEvent(event)) // ОБрабатываем событие закрытия окна
		{
			if (event.type == Event::Closed)
				window.close();
		}

		if (Keyboard::isKeyPressed(Keyboard::Left)) // Если нажата влево сдвием влево и т.д.
		{
			p.dx = -0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			p.dx = 0.1;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			if (p.onGround)
			{
				p.dy = -0.4;
				p.onGround = false;
			}
		}

		p.update(time);
		//enemy.update(time);

		//if (p.rect.intersects(enemy.rect))
		//{
		//	p.sprite.setColor(Color::Red);
		//}

		if (p.rect.left > 1024) offsetX = p.rect.left - 2048 / 2;
		if (p.rect.top > 512) offsetY = p.rect.top - 1024 / 2;

		window.clear(Color::White); // Отчищаем экран

		for(int i = 0; i < H; i++)
			for (int j = 0; j < W; j++)
			{
				if (TileMap[i][j] == 'B')
				{
					rectangle.setTextureRect(IntRect(90, 520, 460, 160));
				}
				if (TileMap[i][j] == '0')
				{
					rectangle.setTextureRect(IntRect(170, 970, 140, 140));
				}

				if (TileMap[i][j] == ' ')
					continue;

				rectangle.setPosition(j * 64 - offsetX, i * 64 - offsetY);
				window.draw(rectangle);
			}
		//window.draw(enemy.sprite);
		window.draw(p.sprite); // Рисуем окружность
		window.display(); // Выводим на дисплей
	}

	return 1;
}