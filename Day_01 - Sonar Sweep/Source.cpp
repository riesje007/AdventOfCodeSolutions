#include <iostream>
#include <vector>

using namespace std;

int main()
{
	int input;
	vector<int> numbers;
	vector<int> threeSums;
	cin >> input;
	while (input >= 0)
	{
		numbers.push_back(input);
		cin >> input;
	}
	for (auto it = numbers.begin(); it != (numbers.begin() + numbers.size() - 2); it++)
	{
		threeSums.push_back(*it + *(it + 1) + *(it + 2));
	}
	int numberOfIncrements(0);
	for (auto it = threeSums.begin(); it != threeSums.end(); it++)
	{
		if (it != threeSums.begin())
			if (*it > *(it - 1))
				numberOfIncrements++;
	}
	cout << "We have found " << numbers.size() << " numbers and " << threeSums.size() << " three-measurement windows." << endl;
	cout << "These windows contain " << numberOfIncrements << " increments in total." << endl;
	return 0;
}