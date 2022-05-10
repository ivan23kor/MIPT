#include "centroids.hpp"
#include <cmath>
#include <cstdlib>
#include <ctime>

typedef std::vector<sf::Color> Centroids;
typedef std::vector<int> ClosestCentroidIndices;

const float EPSILON = 1e-6;

float distance (const sf::Color& c1, const sf::Color& c2)
{
	return sqrt ((c2.r - c1.r) * (c2.r - c1.r) + (c2.g - c1.g) * (c2.g - c1.g) + (c2.b - c1.b) * (c2.b - c1.b) + (c2.a - c1.a) * (c2.a - c1.a));
}

ColorBuf& ColorBuf::operator+=(const sf::Color& c)
{
	count++;
	r += c.r;
	g += c.g;
	b += c.b;
	a += c.a;

	return *this;
}

Centroids initialiseCentroids (const sf::Image& image, int K)
{
	int x = image.getSize().x;
	int y = image.getSize().y;
	int MAX_PIXEL = x * y;

	int rand_value = 0;
	Centroids centroids(K);
	int current_x = 0;
	int current_y = 0;

	srand (time(NULL));
	for (int i = 0; i < K; ++i)
	{
		current_x = rand() % x;
		current_y = rand() % y;

		centroids[i] = image.getPixel(current_x, current_y);
	}

	return centroids;
}

ClosestCentroidIndices findClosestCentroids(const sf::Image& image, const Centroids& centroids)
{
	int x = image.getSize().x;
	int y = image.getSize().y;
	int centroids_size = centroids.size();
	int current_centroid = 0;
	float current_distance = 0.0;
	ClosestCentroidIndices ids(x * y);

	sf::Color current_color;

	for (int i = 0; i < x; ++i)
		for (int j = 0; j < y; ++j)
		{
			current_color = image.getPixel(i, j);
			current_distance = distance(current_color, centroids[0]);
			for (int k = 1; k < centroids_size; ++k)
				if (current_distance - distance(current_color, centroids[k]) > EPSILON)
					current_centroid = k;

			ids[i * x + j] = current_centroid;
		}

	return ids;
}

Centroids computeMeans(const sf::Image& image, const ClosestCentroidIndices& ids, int K)
{
	int x = image.getSize().x;
	int y = image.getSize().y;
	int MAX_PIXEL = x * y;
	std::vector<ColorBuf> buffer(K);

	Centroids centroids(K);

	// Mistake here
	for (int i = 0; i < MAX_PIXEL; ++i)
		buffer[ids[i]] += image.getPixel(i % x, i / x);

	for (int i = 0; i < K; ++i)
		if (buffer[i].count)
		{
			centroids[i].r = buffer[i].r / buffer[i].count;
			centroids[i].g = buffer[i].g / buffer[i].count;
			centroids[i].b = buffer[i].b / buffer[i].count;
			centroids[i].a = buffer[i].a / buffer[i].count;
		}

	return centroids;
}

void changeColors(sf::Image& image, const Centroids& centroids, const ClosestCentroidIndices& ids)
{
	int x = image.getSize().x;
	int y = image.getSize().y;

	for (int i = 0; i < x; ++i)
		for (int j = 0; j < y; ++j)
			image.setPixel(i, j, centroids[ids[i * x + j]]);
}