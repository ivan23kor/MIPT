#include <SFML/Audio.hpp>
#include "cmath"

#define CHANNEL 1
#define FREQUENCY 440
#define SAMPLE_RATE 44100
#define AMPLITUDE 3e4
#define PI 3.14159

int main( int argc, char const *argv[] )
{
	bool loop = true;
	int temp = 0;

    std::vector<sf::Int16> samples( SAMPLE_RATE );
    for (int i = 0; i < SAMPLE_RATE; ++i)
    {
    	if ( ( sin( ( 3 - CHANNEL ) * PI * i * FREQUENCY / SAMPLE_RATE ) < 0.5 ) && ( sin( ( 3 - CHANNEL ) * PI * i * FREQUENCY / SAMPLE_RATE ) > -0.5 ) )
    		temp = 0;
    	else
    		temp = i;
    	samples[i] = (int)( AMPLITUDE * sin( ( 3 - CHANNEL ) * PI * temp * FREQUENCY / SAMPLE_RATE ) );
    }

    sf::SoundBuffer buffer;
	buffer.loadFromSamples( &samples[0], samples.size(), CHANNEL, SAMPLE_RATE );

	sf::Sound sound;
	sound.setBuffer( buffer );
	sound.setLoop( loop );
	sound.play();

	while (1)
	{
		//if (sf::Keyboard::isKeyPressed (sf::Keyboard::A))
		//	map.hero.velocity = Vector2(-V, 0);
	}

    return 0;
}