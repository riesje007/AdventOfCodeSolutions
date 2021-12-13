#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

size_t fuel(int number)
{
	size_t sum(0);
	for (size_t i = 1; i <= number; i++)
		sum += i;
	return sum;
}

int main()
{
	int number;
	char comma;
	vector<int> positions;
	string input;
	getline(cin, input);
	istringstream ss(input, ios_base::in);
	while (!ss.eof())
	{
		ss >> number;
		positions.push_back(number);
		ss >> comma;
	}
	auto minpos = *min_element(positions.begin(), positions.end());
	auto maxpos = *max_element(positions.begin(), positions.end());
	size_t minFuel = INT64_MAX;
	for (size_t i = minpos; i <= maxpos; i++)
	{
		size_t sum(0);
		for (auto it = positions.begin(); it != positions.end(); it++)
		{
			sum += fuel(abs(static_cast<int>(*it - i)));
		}
		minFuel = min(minFuel, sum);
	}
	cout << "Lowest possible fuel consumption:" << minFuel << endl;
	return 0;
}