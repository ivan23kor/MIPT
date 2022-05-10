#include <iostream>
#include <map>

int main(int argc, char const *argv[])
{
	std::map<std::string, std::string> m;
	m["Sister"] = "+7-916-466-98-54";
	m["Dad"] = "+7-910-428-59-06";
	m["Misha"] = "+7-925-722-73-46";
	m["Mom"] = "+7-910-434-36-38";
	m["Ivan"] = "+7-915-176-33-34";

	for (auto it : m)
		std::cout << it.first << " - " << it.second << "\n";

	return 0;
}