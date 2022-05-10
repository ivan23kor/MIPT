#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>

std::string current_string;

auto change_string = [&]( std::string str )
{
	str.erase(std::remove(str.begin(), str.end(), '_'), str.end());
	std::transform( str.begin(), str.end(), str.begin(), ::tolower);

	return str;
};

int main(int argc, char const *argv[])
{
	int N = 0;
	std::vector<std::string> text;

	std::fstream file("input.txt");
	if (!file.is_open())
		return -1;

	file >> N;
	text.resize(N);
	for (int i = 0; i < N; ++i)
		file >> text[i];

	std::transform( text.begin(), text.end(), text.begin(), change_string );

	std::sort( text.begin(), text.end(), [](const std::string& str1, const std::string& str2 )
		{
			return str1 < str2;
		} );

	current_string = text[0];

	auto it = std::unique(text.begin(), text.end());
	text.erase(it, text.end());


	std::for_each( text.begin(), text.end(), [](const std::string& str)
	{
		std::cout << str << "\n";
	} );

	return 0;
}