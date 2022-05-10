#include "Game.hpp"

int main(int argc, char const *argv[])
{
	Game game1;

	game1.Parse( "data.json" );

	std::cout << game1.firstTeam << " vs " << game1.secondTeam << ": "
	<< game1.statistics.firstScore << " - " << game2.statistics.secondScore << '.' << std::endl;
	std::cout << game1.place.city << ", " << game1.place.state << " at " << game1.place.time << " o'clock." << std::endl;

	return 0;
}

void Game::Parse( const std::string& fileName )
{
	std::ifstream file( fileNmae, std::ifstream::binary );

	if ( !file.is_open() )
	{
		std::cout << "Could not open file!\n";
		return;
	}

	Json::Value root;
	file >> root;

	firstTeam = root["firstTeam"].asString();
	secondTeam = root["secondTeam"].asString();

	struct Statistics statisticsValue = root["statistics"];
	statistics.firstScore = statisticsValue["firstScore"].asInt();
	statistics.secondScore = statisticsValue["secondScore"].asInt();
	statistics.FG1 = statisticsValue["FG1"].asInt();
	statistics.FG2 = statisticsValue["FG2"].asInt();
	statistics.3PT1 = statisticsValue["3PT1"].asInt();
	statistics.3PT2 = statisticsValue["3PT2"].asInt();

	struct Place placeValue = root["place"];
	place.state = placeValue["state"];
	place.city = placeValue["city"];
	place.arena = placeValue["arena"];
}