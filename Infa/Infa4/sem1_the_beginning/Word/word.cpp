#include "word.h"
#include <string>
#include <algorithm>

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