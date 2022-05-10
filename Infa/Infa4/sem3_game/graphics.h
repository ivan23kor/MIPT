#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>
#include "vector2.h"

#define PI 3.1415926

struct Icon
{
private:
	sf::Texture texture;
public:
	sf::Sprite sprite;
	std::string filename;
	Vector2 position;
	Vector2 direction;
	int radius;

	// The function sets a sprite with the picture filename into position (x, y)
	void create_sprite();
};