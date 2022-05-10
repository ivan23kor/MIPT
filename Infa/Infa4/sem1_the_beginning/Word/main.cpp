#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include "word.h"

int main(int argc, char const *argv[])
{
	int wordbase_index = 0;
	int word_count = 0;
	int different_words_count = 0;
	int show_count = 0;
	std::vector<Statistics> wordbase;
	std::string input_file = "text.txt";

	std::ifstream file(input_file);
	std::string buffer;
	std::map<std::string, int> text_map;

	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> buffer;
			buffer = prepare(buffer);
			if (text_map.find(buffer) == text_map.end())
			{
				different_words_count++;
				text_map[buffer] = 1;
			}
			else
				text_map[buffer]++;
			word_count++;
		}

		wordbase.resize(different_words_count);

		for (auto it : text_map)
		{
			wordbase[wordbase_index].count = text_map[it.first];
			wordbase[wordbase_index].word = it.first;
			wordbase_index++;
		}

		sort(wordbase.begin(), wordbase.end(), compare);

		file.close();
	}

	std::cout << "How many most used words do you want to see?\t";
	std::cin >> show_count;

	for (int i = 0; i < show_count; ++i)
			std::cout << "The word <" << wordbase[i].word << "> occured " << wordbase[i].count << " times.\n";

	return 0;
}