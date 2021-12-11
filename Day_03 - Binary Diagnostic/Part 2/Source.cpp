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

// Keep the strings in the vector containing the most significant bit at the indicated position
// removing the strings in which the indicated position is not equal to the most significant bit
void KeepMostSignificant(vector<string>& digits, unsigned int position)
{
	if (position > digits.at(0).length() - 1)
	{
		cout << "FAULT: exceeding string length! Abort!" << endl;
		return;
	}
	size_t sigCount(0);
	for (auto it = digits.begin(); it != digits.end(); it++)
	{
		sigCount += static_cast<size_t>(it->at(position) - '0');
	}
	size_t halfSize = digits.size() % 2 ? digits.size() / 2 + 1 : digits.size() / 2;
	int mostSignificant = sigCount >= halfSize ? 1 : 0;
	vector<size_t> removePositions;
	for (auto it = digits.begin(); it != digits.end(); it++)
	{
		if (it->at(position) - '0' != mostSignificant)
			removePositions.push_back(it - digits.begin());
	}
	// Removing elements afterwards because we cannot interate over a changing vector
	auto it = removePositions.end();
	while (it != removePositions.begin() && digits.size() > 1)
		digits.erase(digits.begin() + *(--it));
}

// Does the exact opposite of KeepMostSignificant
void KeepLeastSignificant(vector<string>& digits, unsigned int position)
{
	if (position > digits.at(0).length() - 1)
	{
		cout << "FAULT: exceeding string length! Abort!" << endl;
		return;
	}
	size_t sigCount(0);
	for (auto it = digits.begin(); it != digits.end(); it++)
	{
		sigCount += static_cast<size_t>(it->at(position) - '0');
	}
	size_t halfSize = digits.size() % 2 ? digits.size() / 2 + 1 : digits.size() / 2;
	int leastSignificant = sigCount < halfSize ? 1 : 0;
	vector<size_t> removePositions;
	for (auto it = digits.begin(); it != digits.end(); it++)
	{
		if (it->at(position) - '0' != leastSignificant)
			removePositions.push_back(it - digits.begin());
	}
	// Re-iterating because we cannot interate over a changing vector
	auto it = removePositions.end();
	while (it != removePositions.begin() && digits.size() > 1)
		digits.erase(digits.begin() + *(--it));
}

int main()
{
	int number(0);
	unsigned int stringlength(0);
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
	vector<string> inputsCopy(inputs.size());   // using a copy so we can reuse the same data again
	std::copy(inputs.begin(), inputs.end(), inputsCopy.begin());
	for (unsigned int pos = 0; pos < stringlength; pos++)
	{
		if (inputsCopy.size() == 1)
			break;
		KeepMostSignificant(inputsCopy, pos);
	}
	if (inputsCopy.size() != 1)
	{
		cout << "FAULT: unable to determine oxygen generator rating" << endl;
		return -1;
	}
	int oxyGenRating(BinaryToNumber(inputsCopy.at(0)));
	cout << "Oxygen generator rating: " << inputsCopy.at(0) << ", value: " << oxyGenRating << endl;

	inputsCopy.clear();
	inputsCopy.resize(inputs.size());
	std::copy(inputs.begin(), inputs.end(), inputsCopy.begin());
	for (unsigned int pos = 0; pos < stringlength; pos++)
	{
		if (inputsCopy.size() == 1)
			break;
		KeepLeastSignificant(inputsCopy, pos);
	}
	if (inputsCopy.size() != 1)
	{
		cout << "FAULT: unable to determine CO2 scrubber rating" << endl;
		return -1;
	}
	int COScrubRating(BinaryToNumber(inputsCopy.at(0)));
	cout << "CO2 scrubber rating: " << inputsCopy.at(0) << ", value: " << COScrubRating << endl;
	cout << "Life support rating: " << oxyGenRating * COScrubRating << endl;

	return 0;
}