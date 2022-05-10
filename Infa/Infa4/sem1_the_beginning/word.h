#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>

struct Statistics
{
	int count;
	std::string word;
};

std::string prepare(std::string& buffer)
{
	int result_index = 0;
	std::string result;
	result.resize(buffer.size());

	std::transform (buffer.begin(), buffer.end(), buffer.begin(), ::tolower);

	for (int i = 0; i < buffer.size(); ++i)
	{
		if ((buffer[i] >= 'a') && (buffer[i] <= 'z'))
		{
			result[result_index] = buffer[i];
			result_index++;
		}
	}

	return result;
}

bool compare (const struct Statistics& left, const struct Statistics& right)
{
	return (left.count - right.count) > 0 ? true : false;
}

int main(int argc, char const *argv[])
{
	int wordbase_index = 0;
	int word_count = 0;
	int different_words_count = 0;
	int show_count = 0;
	std::vector<Statistics> wordbase;

	std::ifstream file("text.txt");
	std::string buffer;
	std::map<std::string, int> text_map;

	if (file.is_open())
	{
		while (!file.eof())
		{
			file >> buffer;
			buffer = prepare(buffer);
			std::cout << buffer << std::endl;
			if (text_map.find(buffer) == text_map.end())
			{
				different_words_count++;
				text_map[buffer] = 1;
			}
			else
				text_map[buffer]++;
			word_count++;
		}

		std::cin >> buffer;

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

	std::cout << "How many most used words do you want to see?";
	std::cin >> show_count;

	for (int i = 0; i < show_count; ++i)
			std::cout << "The word <" << wordbase[i].word << "> occured " << wordbase[i].count << " times.\n";

	return 0;
}