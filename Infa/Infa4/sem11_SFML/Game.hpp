#pragma once

#include "json.h"
#include "iostream"
#include <string>

struct Game
{
	std::string firstTeam;
	std::string secondTeam;

	struct Statistics
	{
		int firstScore;
		int secondScore;
		int FG1;
		int FG2;
		int 3PT1;
		int 3PT2;
	} statistics;

	struct Place
	{
		std::string state;
		std::string city;
		std::string arena;
		int time;
	} place;

	void Parse( const std::string& fileName );
};
