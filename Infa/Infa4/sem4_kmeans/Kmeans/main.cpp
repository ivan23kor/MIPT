#include <SFML/Graphics.hpp>
#include <iostream>
#include "centroids.hpp"

const int K = 10;
const int IterationCount = 30;
typedef std::vector<sf::Color> Centroids;
typedef std::vector<int> ClosestCentroidIndices;

int main(int argc, char const *argv[])
{
	ClosestCentroidIndices ids;

	// Load initial picture to the image
	sf::Texture texture;
	texture.loadFromFile("Donov.png");
	sf::Image image = texture.copyToImage();
	texture.update(image);

	// Changing the image
	Centroids centroids = initialiseCentroids (image, K);
	for (int it = 0; it < IterationCount; ++it)
	{
		ids = findClosestCentroids(image, centroids);
		centroids = computeMeans(image, ids, K);
	}
	for (int i = 0; i < K; ++i)
		std::cout << (int)centroids[i].r << ' ' << (int)centroids[i].g << ' ' << (int)centroids[i].b << '\n';
	changeColors(image, centroids, ids);

	// Applying new image to the Sprite
	image.saveToFile("Donov_new.png");
	texture.update(image);
	sf::Sprite photo;
	photo.setTexture(texture);

	// Set the window
	sf::RenderWindow window (sf::VideoMode((image.getSize()).x, (image.getSize()).y), "Kmeans");

	while (window.isOpen())
	{
		// Window closing processing
		sf::Event event;
		while (window.pollEvent(event))
			if (event.type == sf::Event::Closed)
				window.close();

		// Clear the window each cycle
		window.clear(sf::Color(250, 0, 0, 50));

		// Displaying the contents
		window.draw(photo);
		window.display();
	}

	return 0;
}