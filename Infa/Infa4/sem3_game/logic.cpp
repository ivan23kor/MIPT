#include "logic.h"

// Hero functions
Hero::Hero()
{
	position = Vector2(X / 2, Y / 2);
	velocity = Vector2(0, 0);
	radius = 50;
	direction = Vector2(1, 1);
}

void Hero::update(float dt)
{
	position += velocity * dt;
}

Hero::~Hero() {}


// Bullet functions
Bullet::Bullet(const Vector2& position_in, const Vector2& velocity_in, const Vector2& direction_in, int radius_in)
{
	position = position_in;
	velocity = velocity_in;
	direction = direction_in;
	radius = radius_in;
}

void Bullet::update(float dt)
{
	position += velocity * dt;
}

Bullet::~Bullet() {}


// Map functions
Map::Map()
{
	size.x = X;
	size.y = Y;

	Hero hero;
}

int Map::check_border(Vector2& position, Vector2& velocity, float dt)
{
	// Shortcuts for would be coordinates after the update
	int x = position.x + velocity.x * dt;
	int y = position.y + velocity.y * dt;
	int flag = 0; 			// flag = 1 means a border is reached

	if (x > size.x)
	{
		position.x = size.x;
		velocity.x = velocity.y = 0;
		flag = 1;
	}
	if (x < 0)
	{
		position.x = 0;
		velocity.x = velocity.y = 0;
		flag = 1;
	}
	if (y > size.y)
	{
		position.y = size.y;
		velocity.x = velocity.y = 0;
		flag = 1;
	}
	if (y < 0)
	{
		position.y = 0;
		velocity.x = velocity.y = 0;
		flag = 1;
	}

	return flag;
}

void Map::update(float dt)
{
	if (this->check_border(hero.position, hero.velocity, dt) == 0)
		hero.update(dt);

	for (int i = 0; i < bullets.size(); ++i)
	{
		if (this->check_border(bullets[i].position, bullets[i].velocity, dt) == 0)
			bullets[i].update(dt);
		else
			bullets.erase(bullets.begin() + i);
	}
}

void Map::add_bullet()
{
	Vector2 bullet_position(hero.position + hero.direction.norm() * BULLET_OFFSET);
	Vector2 bullet_velocity(hero.direction.norm() * BULLET_SPEED);

	Bullet temp(bullet_position, bullet_velocity, -hero.direction.normal(), BULLET_SIZE);

	bullets.push_back(temp);
}

Map::~Map() {}