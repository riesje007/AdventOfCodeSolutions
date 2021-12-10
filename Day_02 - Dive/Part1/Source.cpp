#include <iostream>
#include <string>

using namespace std;

int main()
{
	string action;
	int amount(0), depth(0), position(0);
	bool fault(false);
	cin >> action >> amount;
	while (amount >= 0)
	{
		if (action == "up")
			depth -= amount;
		else if (action == "down")
			depth += amount;
		else if (action == "forward")
			position += amount;
		else
		{
			fault = true;
			break;
		}
		cin >> action >> amount;
	}
	if (fault)
		cout << "There was a problem with the input, unable to process. Please make sure it is correct." << endl;
	else
	{
		cout << "Your position: " << position << ". Your depth: " << depth << "." << endl;
		cout << "Result: " << position * depth << "." << endl;
	}

	return 0;
}