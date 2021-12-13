#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class point
{
public:
	int x;
	int y;

public:
	point()
	{
		x = 0;
		y = 0;
	}

	point(int xcoord, int ycoord)
	{
		x = xcoord;
		y = ycoord;
	}

	bool isStraightOrDiagonal(point p1)
	{
		return (p1.x == x || p1.y == y || abs(p1.x - x) == abs(p1.y - y));
	}

	// return value 1 = horizontal, 2 = vertical, 3 = pure diagonal (0 = none)
	unsigned int typeOfStraightLine(point p1)
	{
		if (p1.x == x && p1.y != y)
			return 2;
		if (p1.x != x && p1.y == y)
			return 1;
		if (abs(p1.x - x) == abs(p1.y - y))
			return 3;
		return 0;
	}

	int minX(point p1)
	{
		return min(p1.x, x);
	}

	int minY(point p1)
	{
		return min(p1.y, y);
	}

	int maxX(point p1)
	{
		return max(p1.x, x);
	}

	int maxY(point p1)
	{
		return max(p1.y, y);
	}
};

void print_matrix(vector<int>& mtrx, int rowWidth)
{
	for (auto it = mtrx.begin(); it != mtrx.end(); it++)
	{
		if (*it == 0)
			cout << ".";
		else
			cout << *it;
		if (!((it - mtrx.begin() + 1) % rowWidth))
			cout << endl;
	}
	cout << endl;
}

int main()
{
	string input, arrow;
	char comma;
	int x1, y1, x2, y2;
	vector<point> points;
	getline(cin, input);
	point p1, p2;
	while (input != "stop")
	{
		if (input.length() > 0)
		{
			stringstream iss(input, ios_base::in);
			iss >> x1 >> comma >> y1 >> arrow >> x2 >> comma >> y2;
			p1 = point(x1, y1);
			p2 = point(x2, y2);
			if (p1.isStraightOrDiagonal(p2))
			{
				points.push_back(p1);
				points.push_back(p2);
			}
		}
		getline(cin, input);
	}
	int minX(INT_MAX), maxX(0), minY(INT_MAX), maxY(0);
	for (auto it = points.begin(); it != points.end(); it++)
	{
		minX = min(minX, it->x);
		maxX = max(maxX, it->x);
		minY = min(minY, it->y);
		maxY = max(maxY, it->y);
	}

	size_t rowWidth = static_cast<size_t>(maxX + 1);
	size_t colHeight = static_cast<size_t>(maxY + 1);
	vector<int> matrix((rowWidth) * (colHeight));
	for (auto it = matrix.begin(); it != matrix.end(); it++)
		*it = 0;
	for (size_t pos = 0; pos < points.size() - 1; pos += 2)
	{
		p1 = points.at(pos);
		p2 = points.at(pos + 1);
		minX = p1.minX(p2);
		minY = p1.minY(p2);
		maxX = p1.maxX(p2);
		maxY = p1.maxY(p2);
		int lineType = p1.typeOfStraightLine(p2);
		if (lineType == 1)
		{
			for (int pos = minX + minY * rowWidth; pos <= maxX + minY * rowWidth; pos++)
				matrix.at(pos)++;
		}
		else if (lineType == 2)
		{
			for (int pos = minX + minY * rowWidth; pos <= minX + maxY * rowWidth; pos += rowWidth)
				matrix.at(pos)++;
		}
		else if (lineType == 3)
		{
			int increment = rowWidth;
			if (p1.y > p2.y)
				increment = -1 * rowWidth;
			if (p1.x > p2.x)
				increment--;
			else
				increment++;
			int endPos = p2.x + p2.y * rowWidth;
			if (p2.y > p1.y)
				for (int pos = p1.x + p1.y * rowWidth; pos <= endPos; pos += increment)
					matrix.at(pos)++;
			else
				for (int pos = p1.x + p1.y * rowWidth; pos >= endPos; pos += increment)
					matrix.at(pos)++;
		}
#ifdef _DEBUG
		print_matrix(matrix, rowWidth);
#endif
	}
	unsigned int count(0);
	for (auto it = matrix.begin(); it != matrix.end(); it++)
	{
		if (*it >= 2)
			count++;
	}
	cout << "We have " << count << " points with at least 2 lines of overlap." << endl;
	return 0;
}