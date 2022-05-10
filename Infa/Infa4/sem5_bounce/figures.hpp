#pragma once
#include "vector2.h"

const int X = 1200;
const int Y = 700;
const float V = 1;
#define EPSILON 1e-4

class MaterialPoint
{
public:
	MaterialPoint(int x, int y, const float& mass_in);
	~MaterialPoint();

	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	float mass;

	void updatePosition (float dt);
	Vector2 getImpulse() const;
};

class Ball : public MaterialPoint
{
public:
	Ball(int x, int y, const float& mass_in, const float& radius_in, int type_in);
	~Ball();
	float radius;
	int type;
};