#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int BinaryToNumber(string digits)
{
	int number(0);
	for (int pos = 0; pos < digits.length(); pos++)
	{
		number <<= 1;
		number |= digits[pos] - '0';
	}
	return number;
}

string ones(unsigned int length)
{
	string allOnes("");
	while (length > 0)
	{
		allOnes += "1";
		length--;
	}
	return allOnes;
}

int main()
{
	int number(0), stringlength(0);
	string input;
	vector<string> inputs;
	cin >> input;
	while (input != "stop")
	{
		if (stringlength == 0)
			stringlength = static_cast<int>(input.length());
		inputs.push_back(input);
		cin >> input;
	}
	vector<int> significants(stringlength);
	for (auto it = significants.begin(); it != significants.end(); it++)
		*it = 0;
	for (auto it = inputs.begin(); it != inputs.end(); it ++)
	{
		for (int pos = 0; pos < stringlength; pos++)
		{
			significants.at(pos) += it->at(pos) - '0';
		}
	}
	input.clear();
	for (auto it = significants.begin(); it != significants.end(); it++)
		input += *it > (inputs.size() / 2) ? '1' : '0';
	cout << "Gamma based on most significant bit: " << input << endl;
	int gamma(BinaryToNumber(input));
	int epsilon = ~gamma & BinaryToNumber(ones(stringlength));
	cout << "Gamma found: " << gamma << endl;
	cout << "Epsilon found: " << epsilon << endl;
	cout << "Power consumption: " << gamma * epsilon << endl;
	return 0;
}