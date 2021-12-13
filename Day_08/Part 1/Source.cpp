#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
	string input;
	getline(cin, input);
	istringstream numbers(input, ios_base::in);
	vector<int> nums;
	string number;
	int numberCount(0);
	while (input != "stop")
	{
		while (number != "|")
			numbers >> number;
		while (!numbers.eof())
		{
			numbers >> number;
			if (number.length() == 2 || number.length() == 3 ||
				number.length() == 4 || number.length() == 7)
				numberCount++;
		}
		getline(cin, input);
		numbers = istringstream(input, ios_base::in);
	}
	cout << "The numbers we were looking for (1, 4, 7, 8) appear " << numberCount
		<< " times in total." << endl;
	return 0;
}