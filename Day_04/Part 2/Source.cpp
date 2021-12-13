#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

typedef struct
{
	int score;
	int atdraw;
	bool winner;
	vector<int> board;
} player;

int MarkDrawOnBoards(vector<player>& players, unsigned int numberDrawn, unsigned int rowLength)
{
	unsigned int colLength = static_cast<int>(players.at(0).board.size()) / rowLength;
	bool winner = false;
	bool numberHit = false;
	int score = -1;
	for (auto outerIt = players.begin(); outerIt != players.end(); outerIt++)
	{
		numberHit = false;
		winner = false;
		for (auto innerIt = outerIt->board.begin(); innerIt != outerIt->board.end(); innerIt++)
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
				auto it = outerIt->board.begin() + static_cast<size_t>(col);
				for (int i = 0; i < colLength; i++)
					sum += *(it + i * rowLength);
				if (sum <= static_cast<int>(-1 * colLength) && !outerIt->winner)
				{
					winner = true;
					break;
				}
				sum = 0;
			}
			sum = 0;
			for (unsigned int row = 0; row < colLength && !winner; row++)
			{
				for (auto it = outerIt->board.begin() + (size_t)row * (size_t)rowLength; (size_t)(it - outerIt->board.begin()) < (size_t)rowLength * ((size_t)row + 1); it++)
				{
					sum += *it;
				}
				if (sum <= static_cast<int>(-1 * rowLength) && !outerIt->winner)
				{
					winner = true;
					break;
				}
				sum = 0;
			}
			if (winner && !outerIt->winner)
			{
				score = 0;
				for (auto it = outerIt->board.begin(); it != outerIt->board.end(); it++)
				{
					if (*it >= 0)
						score += *it;
				}
				outerIt->score = (score >= 0) ? score : outerIt->score;
				outerIt->winner = true;
				outerIt->atdraw = numberDrawn;
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
	vector<player> players;
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
			{
				player pl;
				pl.atdraw = -1;
				pl.board = board;
				pl.score = 0;
				pl.winner = false;
				players.push_back(pl);
			}
			board.clear();
		}
		getline(cin, line);
	}
	if (CheckBoard(board) and board.size() > 0)
	{
		player pl;
		pl.atdraw = -1;
		pl.board = board;
		pl.score = 0;
		pl.winner = false;
		players.push_back(pl);
	}

	int retValue = -1;
	int draw = -1;
	int numNoWin(1);
	for (auto it = draws.begin(); it != draws.end() && numNoWin > 0; it++)
	{
		draw = *it;
		retValue = MarkDrawOnBoards(players, draw, rowlength);
		numNoWin = 0;
		for (auto it = players.begin(); it != players.end(); it++)
			numNoWin += it->winner ? 0 : 1;
	}
	if (retValue < 1)
		cout << "FAULT: We did not find a winner" << endl;
	else
		cout << "We have a winner with score " << retValue << " at draw " << draw << ", resulting in final score: " << draw * retValue << endl;
	return 0;
}