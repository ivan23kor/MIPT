#include <SFML/Graphics.hpp>
#include "vector2.h"
#include "figures.hpp"

const float DEFAULT_MASS = 100.0;
const float DEFAULT_RADIUS = 20.0;
const float ADD_TIME = 200.0;

int main(int argc, char const *argv[])
{
	// Vector of our balls
	std::vector<Ball> balls;

	// Outlook of those balls
	sf::CircleShape ball_outlook;

	Vector2 d;
	Vector2 dp;

	// Time variables
	sf::Clock clock;
	sf::Time time = clock.getElapsedTime();
	float previous_time = time.asMilliseconds();
	float previous_add_time = time.asMilliseconds();
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

		// Add new ball if mouse is pressed
		if ((sf::Mouse::isButtonPressed(sf::Mouse::Left)) && (previous_time - previous_add_time > ADD_TIME))
		{
			balls.push_back({sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y, DEFAULT_MASS, DEFAULT_RADIUS, 0});
			previous_add_time = time.asMilliseconds();
		}

		// dt calculations
		time = clock.getElapsedTime();
		dt = time.asMilliseconds() - previous_time;

		for (int i = 0; i < balls.size(); ++i)
		{
			for (int j = i + 1; j < balls.size(); ++j)
			{
				d = balls[j].position - balls[i].position;
				if ((balls[j].radius + balls[j].radius - d.len() > EPSILON) && ((balls[j].velocity - balls[i].velocity) * d < -EPSILON))
				{
					dp = 2 * ((balls[j].velocity - balls[i].velocity) / (1 / balls[j].mass + 1 / balls[i].mass)) * d.norm() * d.norm();
					balls[j].velocity -= dp / balls[j].mass;
					balls[i].velocity += dp / balls[i].mass;
				}
			}

			balls[i].updatePosition(dt);

			ball_outlook.setPosition(balls[i].position.x, balls[i].position.y);
			ball_outlook.setRadius(DEFAULT_RADIUS);
			ball_outlook.setFillColor(sf::Color(200 * i, 200 * (i + 1), 100));
			window.draw(ball_outlook);
		}

		// previous_time calculations
		time = clock.getElapsedTime();
		previous_time = time.asMilliseconds();

		window.display();
	}

	return 0;
}