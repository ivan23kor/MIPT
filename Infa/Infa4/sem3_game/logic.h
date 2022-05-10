#pragma once
#include <SFML/Graphics.hpp>
#include "vector2.h"

#define X 1200
#define Y 700

#define PI 3.1415926
#define BULLET_OFFSET 10	//~ this distance from the hero bullets is shot
#define BULLET_SIZE 12
#define BULLET_SPEED 2

struct Hero
{
	Vector2 position; 				//the position of the center of the hero
	Vector2 velocity;
	Vector2 direction; 				//the direction the hero looks onto
	int radius;
	
	Hero();
	void update(float dt);
	~Hero();
};

struct Bullet
{
	Vector2 position;
	Vector2 velocity;
	Vector2 direction;
	int radius;

	Bullet(const Vector2& position_in, const Vector2& velocity_in, const Vector2& direction_in, int radius_in);
	void update(float dt);
	~Bullet();
};

struct Map
{
	Vector2 size;
	Hero hero;
	std::vector<Bullet> bullets;

	Map();
	int check_border(Vector2& position, Vector2& velocity, float dt); 	//returns 1 if a border is reached, 0 otherwise
	void update(float dt);
	void add_bullet();
	//void remove_bullet();
	~Map();
};