#include <iostream>
#include <deque>
#include <sstream>
#include <vector>

using namespace std;


int main()
{
	deque<size_t> lanternfish;
	int dayCount(256);
	lanternfish.resize(9, 0);
	string input, verb1, verb2;
	getline(cin, input);
	char comma;
	int number;
	size_t totalFish(0);
	istringstream inputs(input, ios_base::in);
	inputs >> verb1 >> verb2;
	if (verb1 + verb2 == "Initialstate:")
	{
		while (!inputs.eof())
		{
			inputs >> number;
			lanternfish.at(number)++;
			inputs >> comma;
		}
		for (int day = 1; day <= dayCount; day++)
		{
			size_t num = lanternfish.at(0);
			lanternfish.pop_front();
			lanternfish.push_back(num);
			lanternfish.at(6) += num;
		}
		for (auto& num : lanternfish)
			totalFish += num;
		cout << "After " << dayCount << " days: " << totalFish << " fish" << endl;
	}

	return 0;
}