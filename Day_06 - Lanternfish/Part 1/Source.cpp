#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

void output(vector<int>& fishies, int day)
{
	cout << "After " << day;
	if (day > 1)
		cout << " days: ";
	else
		cout << " day: ";
	cout << fishies.at(0);
	for (auto it = fishies.begin() + 1; it != fishies.end(); it++)
	{
		cout << "," << *it;
	}
	cout << endl;
}

int main()
{
	vector<int> lanternfish;
	string input, verb1, verb2;
	getline(cin, input);
	char comma;
	int number;
	istringstream inputs(input, ios_base::in);
	inputs >> verb1 >> verb2;
	if (verb1 + verb2 == "Initialstate:")
	{
		size_t counter(0);
		while (!inputs.eof())
		{
			inputs >> number;
			lanternfish.push_back(number);
			inputs >> comma;
		}
		//cout << "So we start off with " << lanternfish.size() << " fish." << endl;
		int daycount = 256;
		for (int day = 1; day <= daycount; day++)
		{
			int newFish(0);
			for (auto it = lanternfish.begin(); it != lanternfish.end(); it++)
			{
				if (*it == 0)
				{
					*it = 6;
					newFish++;
				}
				else
					(*it)--;
			}
			for (int i = 0; i < newFish; i++)
			{
					lanternfish.push_back(8);
			}
		}
		size_t totalFish(lanternfish.size());
		cout << "After " << daycount << " days: " << lanternfish.size() << " fish" << endl;
	}

	return 0;
}