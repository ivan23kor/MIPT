#include <SFML/Graphics.hpp>
#include <iostream>
#include "logic.h"
#include "graphics.h"

const float V = .7;

int main(int argc, char const *argv[])
{
	// Initialise map
	Map map;

	// Hero's outlook
	Icon hero_icon;
	hero_icon.filename = "Superman.png";
	hero_icon.radius = 50;
	// Bullets' outlook
	std::vector<Icon> bullet_icon;
	Icon temp_bullet;
	temp_bullet.filename = "Bullet.png";
	temp_bullet.radius = BULLET_SIZE;
	int bullet_icon_index = 0;

	sf::Vector2i mousePosition;
	// Time variables
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	float previous_time = time.asMilliseconds();
	float dt = 0.0;

	// Set the window
	sf::RenderWindow window (sf::VideoMode(X, Y), "Game");

	while (window.isOpen())
	{
		// Window closing processing
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		// Clear the window each cycle
		window.clear(sf::Color(200, 245, 255, 0));

		// dt calculations
		time = clock.getElapsedTime();
		dt = time.asMilliseconds() - previous_time;

		// previous_time calculations
		time = clock.getElapsedTime();
		previous_time = time.asMilliseconds();

		// ASWD movements
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::A))
			map.hero.velocity = Vector2(-V, 0);
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::D))
			map.hero.velocity = Vector2(V, 0);
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::W))
			map.hero.velocity = Vector2(0, -V);
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::S))
			map.hero.velocity = Vector2(0, V);

		// Follow the cursor
		mousePosition = sf::Mouse::getPosition(window);
		map.hero.direction.x = mousePosition.x - map.hero.position.x;
		map.hero.direction.y = mousePosition.y - map.hero.position.y;

		// Creating new bullet if left-click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			map.add_bullet();
			temp_bullet.position = map.bullets[bullet_icon_index].position;
			temp_bullet.direction = map.bullets[bullet_icon_index].direction;
			bullet_icon.push_back(temp_bullet);
			bullet_icon_index++;
		}

		// Apply the moves
		map.update(dt);

		// Make hero's velocity equal to zero after the move
		map.hero.velocity = Vector2(0,0);

		// Drawing the hero
		hero_icon.position = map.hero.position;
		hero_icon.direction = map.hero.direction;
		
		/* вы на каждом кадре считываете текстуру с диска (из файла) ... это очень расточительно. Так не надо делать. */
		hero_icon.create_sprite();
		window.draw(hero_icon.sprite);

		// Displaying the contents
		bullet_icon_index = map.bullets.size();
		
		// вам не нужно хранить целый массив иконок ... все пули ведь с помощью одной текстуры отрисовываются.
		bullet_icon.resize(bullet_icon_index);
		for (int i = 0; i < bullet_icon_index; ++i)
		{
			bullet_icon[i].position = map.bullets[i].position;
			bullet_icon[i].direction = map.bullets[i].direction;
			bullet_icon[i].create_sprite();
			window.draw(bullet_icon[i].sprite);
		}
		window.display();
	}

	return 0;
}
