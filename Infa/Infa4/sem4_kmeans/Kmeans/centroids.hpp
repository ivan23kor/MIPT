#pragma once
#include <SFML/Graphics.hpp>

typedef std::vector<sf::Color> Centroids;
typedef std::vector<int> ClosestCentroidIndices;

struct ColorBuf
{
	int r, g, b, a;
	int count;

	ColorBuf& operator+=(const sf::Color& c);
};

float distance (const sf::Color& c1, const sf::Color& c2);
Centroids initialiseCentroids (const sf::Image& image, int K);
ClosestCentroidIndices findClosestCentroids(const sf::Image& image, const Centroids& centroids);
Centroids computeMeans(const sf::Image& image, const ClosestCentroidIndices& ids, int K);
void changeColors(sf::Image& image, const Centroids& centroids, const ClosestCentroidIndices& ids);