#pragma once
#include <string>

struct Statistics
{
	int count;
	std::string word;
};

std::string prepare(std::string& buffer);

bool compare (const struct Statistics& left, const struct Statistics& right);