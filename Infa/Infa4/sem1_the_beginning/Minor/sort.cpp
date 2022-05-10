#include <algorithm>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool operator> (const string& left, const string& right)
{
	cout << "!";
	if (left.size () > right.size ())
		return true;
	else if (left.size () < right.size ())
		return false;
	else if (left > right)
		return true;
	else
		return false;
}

bool operator== (const string& left, const string& right)
{
	cout << "!";
	if ((left.size () == right.size ()) && (left == right))
		return true;
	else
		return false;
}

int main(int argc, char const *argv[])
{
	int strings_count = 0;
	vector<string> v;

	cin >> strings_count;
	v.resize (strings_count);
	for (int i = 0; i < strings_count; ++i)
		cin >> v[i];

	sort (v.begin (), v.end ());

	cout << "Your sorted array is: ";
	for (int i = 0; i < strings_count; ++i)
		cout << v[i] << " ";

	return 0;
}