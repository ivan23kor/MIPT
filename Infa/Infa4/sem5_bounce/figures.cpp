#include "figures.hpp"
#include <ctime>
#include <cstdlib>
#include <cmath>

MaterialPoint::MaterialPoint(int x, int y, const float& mass_in)
{
	int random_value = 0;
	position.x = x;
	position.y = y;

	srand(time(NULL));
	random_value = rand();

	velocity.x = cos(random_value) * V;
	velocity.y = sin(random_value) * V;

	acceleration = Vector2(0, 0);

	mass = mass_in;
}

void MaterialPoint::updatePosition(float dt)
{
	Vector2 future_position(position + velocity * dt);

	if (future_position.x < EPSILON)
	{
		future_position.x *= -1;
		velocity.x *= -1;
	}
	if (future_position.y < EPSILON)
	{
		future_position.y *= -1;
		velocity.y *= -1;
	}
	if (future_position.x - X > EPSILON)
	{
		future_position.x = 2 * X - future_position.x;
		velocity.x *= -1;
	}
	if (future_position.y - Y > EPSILON)
	{
		future_position.y = 2 * Y - future_position.y;
		velocity.y *= -1;
	}

	position = future_position;
}

Vector2 MaterialPoint::getImpulse() const
{
	return mass * velocity;
}

MaterialPoint::~MaterialPoint() {}

Ball::Ball(int x, int y, const float& mass_in, const float& radius_in, int type_in) : MaterialPoint(x, y, mass_in)
{
	radius = radius_in;

	type = type_in;
}

Ball::~Ball() {}