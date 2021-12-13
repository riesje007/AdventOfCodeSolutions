#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

int MarkDrawOnBoards(vector<vector<int>>& boards, unsigned int numberDrawn, unsigned int rowLength)
{
	unsigned int colLength = static_cast<int>(boards.at(0).size()) / rowLength;
	bool winner = false;
	bool numberHit = false;
	int score = -1;
	for (auto outerIt = boards.begin(); outerIt != boards.end(); outerIt++)
	{
		numberHit = false;
		for (auto innerIt = outerIt->begin(); innerIt != outerIt->end(); innerIt++)
		{
			if (*innerIt == numberDrawn)
			{
				*innerIt = -1;
				numberHit = true;
				break;
			}
		}
		if (numberHit)
		{
			int sum = 0;
			for (unsigned int col = 0; col < rowLength; col++)
			{
				for (auto it = outerIt->begin() + col; it - outerIt->begin() < outerIt->end() - rowLength + col - outerIt->begin(); it += rowLength)
				{
					sum += *it;
				}
				if (sum <= static_cast<int>(-1 * colLength))
				{
					winner = true;
					break;
				}
				sum = 0;
			}
			sum = 0;
			for (unsigned int row = 0; row < colLength && !winner; row++)
			{
				for (auto it = outerIt->begin() + (size_t)row * (size_t)rowLength; (size_t)(it - outerIt->begin()) < (size_t)rowLength * ((size_t)row + 1); it++)
				{
					sum += *it;
				}
				if (sum <= static_cast<int>(-1 * rowLength))
				{
					winner = true;
					break;
				}
				sum = 0;
			}
			if (winner)
			{
				score = 0;
				for (auto it = outerIt->begin(); it != outerIt->end(); it++)
				{
					if (*it >= 0)
						score += *it;
				}
				return score;
			}
		}
	}
	return score;
}

bool CheckBoard(vector<int> board)
{
	vector<int> uniques;
	for (auto it = board.begin(); it != board.end(); it++)
	{
		if (uniques.size() > 0 && find(uniques.begin(), uniques.end(), *it) == uniques.end())
			uniques.push_back(*it);
		else if (uniques.size() > 0)
		{
			cout << "FAULT: number in board not unique." << endl;
			return false;
		}
		else
			uniques.push_back(*it);
	}
	return true;
}

int main()
{
	string line;
	vector<int> draws;
	getline(cin, line);
	char c;
	int number;
	istringstream items(line, ios_base::in);
	while (!items.eof())
	{
		items >> number;
		draws.push_back(number);
		items >> c;
	}
	getline(cin, line);
	vector<int> board;
	vector<vector<int>> boards;
	unsigned int rowlength(0);
	while (line != "stop")
	{
		if (line.length() > 0)
		{
			items = istringstream(line, ios_base::in);
			while (!items.eof())
			{
				items >> number;
				board.push_back(number);
			}
			if (rowlength == 0)
				rowlength = static_cast<unsigned int>(board.size());
		}
		else if (board.size() > 0)
		{
			if (CheckBoard(board))
				boards.push_back(board);
			board.clear();
		}
		getline(cin, line);
	}
	boards.push_back(board);

	int retValue = -1;
	int draw = -1;
	for (auto it = draws.begin(); it != draws.end() && retValue < 0; it++)
	{
		draw = *it;
		retValue = MarkDrawOnBoards(boards, draw, rowlength);
	}
	if (retValue < 1)
		cout << "FAULT: We did not find a winner" << endl;
	else
		cout << "We have a winner with score " << retValue << " at draw " << draw << ", resulting in final score: " << draw * retValue << endl;
	return 0;
}