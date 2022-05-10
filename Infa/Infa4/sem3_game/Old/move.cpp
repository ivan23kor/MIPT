#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>

#define X 1000
#define Y 800
const float V = .7f;
const float PI = 3.14159f;

int main(int argc, char const *argv[])
{
	int previous_time = 0;
	int delta_time = 0;

	sf::Clock clock;

	sf::RenderWindow window (sf::VideoMode(X, Y), "Moving shapes");

	// Time processing
	sf::Time time = clock.getElapsedTime();
	previous_time = time.asSeconds();

	// Adding a picture on to the object
	sf::Texture texture;
	texture.loadFromFile ("iPad-2.png");
	sf::Sprite circle (texture);
	circle.setPosition (X / 2, Y / 2);
	circle.setScale (.4f, .4f);
	sf::Vector2u circleSize = circle.getTexture()->getSize();
	circle.setOrigin (circleSize.x / 2, circleSize.y / 2);

	// The object follows the mouse
	sf::Vector2i mousePosition = sf::Mouse::getPosition (window);
	sf::Vector2f center = circle.getPosition();
	sf::Vector2f d = sf::Vector2f (mousePosition.x, mousePosition.y) - center;

	while (window.isOpen())
	{
		// Window closing processing
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		window.clear(sf::Color(250, 250, 0, 0));

		// Time calculations
		time = clock.getElapsedTime();
		delta_time = time.asMilliseconds() - previous_time;
		time = clock.getElapsedTime();
		previous_time = time.asMilliseconds();
		std::cout << delta_time << "\n";

		// Keyboard response processing
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Left))
			circle.move (-delta_time * V, 0);
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Right))
			circle.move (delta_time * V, 0);
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Up))
			circle.move (0, -delta_time * V);
		if (sf::Keyboard::isKeyPressed (sf::Keyboard::Down))
			circle.move (0, delta_time * V);

		// The object follows the mouse
		mousePosition = sf::Mouse::getPosition (window);
		center = circle.getPosition();
		d = sf::Vector2f (mousePosition.x, mousePosition.y) - center;
		circle.setRotation (90 + atan2f(d.y, d.x) * 180 / PI);

		window.draw(circle);
		window.display();
	}
	return 0;
}