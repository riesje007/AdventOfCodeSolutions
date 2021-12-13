#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
using namespace std;

vector<int> values;
map<int, int> Digits;
map<char, char> CharDecodingMap;

void initialize()
{
	values.push_back(1);
	values.push_back(2);
	values.push_back(3);
	values.push_back(4);
	values.push_back(11);
	values.push_back(6);
	values.push_back(7);
	Digits.emplace(pair<int, int>(30, 0));
	Digits.emplace(pair<int, int>(9, 1));
	Digits.emplace(pair<int, int>(26, 2));
	Digits.emplace(pair<int, int>(21, 3));
	Digits.emplace(pair<int, int>(15, 4));
	Digits.emplace(pair<int, int>(20, 5));
	Digits.emplace(pair<int, int>(31, 6));
	Digits.emplace(pair<int, int>(10, 7));
	Digits.emplace(pair<int, int>(34, 8));
	Digits.emplace(pair<int, int>(23, 9));
}

int GetValue(string input)
{
	int sum(0);
	for (auto& lt : input)
		sum += values.at(static_cast<size_t>(lt) - static_cast<size_t>('a'));
	return sum;
}

int GetDigit(int value)
{
	return Digits[value];
}

int GetDigit(string input)
{
	return Digits[GetValue(input)];
}

char OneToSixNineZero(string& one, vector<string>& sixninezero)
{
	for (auto& ltr : one)
	{
		for (auto str = sixninezero.begin(); str != sixninezero.end(); str++)
		{
			if (find(str->begin(), str->end(), ltr) == str->end())
			{
				str->append("#");
				return ltr;
			}
		}
	}
	return 'z';
}

void DecodeInput(vector<string>& inputs)
{
	string one, seven, six, nine, zero, four, two, five, three, eight;
	vector<string> sixLongs, fiveLongs;
	char top(0), bottom(0), middle(0), lefttop(0), leftbottom(0), righttop(0), rightbottom(0);
	for (auto& num : inputs)
	{
		if (num.length() == 2)
			one = num;
		else if (num.length() == 3)
			seven = num;
		else if (num.length() == 4)
			four = num;
		else if (num.length() == 7)
			eight = num;
		else if (num.length() == 6)
			sixLongs.push_back(num);
		else if (num.length() == 5)
			fiveLongs.push_back(num);
	}

	for (auto& ltr : seven)
	{
		if (find(one.begin(), one.end(), ltr) == one.end())
		{
			top = ltr;
			break;
		}
	}
	auto ltr = OneToSixNineZero(one, sixLongs);
	if (ltr == 'z')
		cout << "FAULT: criteria onetosixninezero mapping NOT fulfilled!" << endl;
	righttop = ltr;
	for (auto str = sixLongs.begin(); str != sixLongs.end(); str++)
	{
		if (str->at(str->length() - 1) == '#')
		{
			six = str->substr(0, str->length() - 2);
			sixLongs.erase(str);
			break;
		}
	}
	for (auto& lt : one)
	{
		if (lt != ltr)
		{
			rightbottom = lt;
			break;
		}
	}
	for (auto& str : fiveLongs)
	{
		if (find(str.begin(), str.end(), righttop) == str.end())
			five = str;
		else if (find(str.begin(), str.end(), rightbottom) != str.end())
			three = str;
		if (find(str.begin(), str.end(), rightbottom) == str.end())
			two = str;
	}
	fiveLongs.clear();
	for (auto& lt : five)
	{
		if (find(four.begin(), four.end(), lt) == four.end() && lt != top)
		{
			bottom = lt;
			break;
		}
	}
	for (auto& str : sixLongs)
	{
		bool found(false);
		for (auto& lt : four)
		{
			if (find(str.begin(), str.end(), lt) == str.end())
			{
				zero = str;
				found = true;
				break;
			}
		}
		if (found)
			continue;
		else
			nine = str;
	}
	sixLongs.clear();
	for (auto& lt : eight)
	{
		if (find(five.begin(), five.end(), lt) == five.end() && lt != righttop)
			leftbottom = lt;
		if (find(two.begin(), two.end(), lt) == two.end() && lt != rightbottom)
			lefttop = lt;
		if (find(zero.begin(), zero.end(), lt) == zero.end())
			middle = lt;
	}

	CharDecodingMap.emplace(pair<char, char>(top, 'a'));
	CharDecodingMap.emplace(pair<char, char>(lefttop, 'b'));
	CharDecodingMap.emplace(pair<char, char>(righttop, 'c'));
	CharDecodingMap.emplace(pair<char, char>(middle, 'd'));
	CharDecodingMap.emplace(pair<char, char>(leftbottom, 'e'));
	CharDecodingMap.emplace(pair<char, char>(rightbottom, 'f'));
	CharDecodingMap.emplace(pair<char, char>(bottom, 'g'));
}

int DecodeTargets(vector<string>& targetStrings)
{
	string intermediate, result;
	for (auto& str : targetStrings)
	{
		for (auto& lt : str)
			intermediate += CharDecodingMap[lt];
		result += GetDigit(GetValue(intermediate)) + '0';
		intermediate.clear();
	}
	return stoi(result);
}


int main()
{
	initialize();
	string input;
	getline(cin, input);
	string num;
	vector<string> theInputs;
	vector<string> nums;
	vector<string> targets;
	int theSum(0);
	while (input != "stop")
	{
		theInputs.push_back(input);
		getline(cin, input);
	}
	for (auto& str : theInputs)
	{
		istringstream ins(str, ios_base::in);
		ins >> num;
		while (num != "|")
		{
			nums.push_back(num);
			ins >> num;
		}
		while (!ins.eof())
		{
			ins >> num;
			targets.push_back(num);
		}
		DecodeInput(nums);
		int theResult = DecodeTargets(targets);
		theSum += theResult;
		cout << "This results in: " << DecodeTargets(targets) << endl;
		CharDecodingMap.clear();
		nums.clear();
		targets.clear();
	}
	cout << "All adding up to: " << theSum << endl;
	return 0;
}