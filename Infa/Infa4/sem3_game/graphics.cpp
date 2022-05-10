#include "graphics.h"

void Icon::create_sprite()
{
	float scale_x = 0.0;
	float scale_y = 0.0;

	// Loading a picture
	texture.loadFromFile (filename);
	sprite.setTexture (texture);

	// Setting the scale
	scale_x = 2 * radius / sprite.getTexture()->getSize().x;
	scale_y = 2 * radius / sprite.getTexture()->getSize().y;

	// Setting position and size
	sprite.setPosition (position.x, position.y);
	sprite.setScale (.2f, .2f);			// inputting scale_x and scale_y yields an error
	sf::Vector2u circleSize = sprite.getTexture()->getSize();
	sprite.setOrigin (circleSize.x / 2, circleSize.y / 2);

	// Setting rotation
	sprite.setRotation(90 + atan2f(direction.y, direction.x) * 180 / PI);
}