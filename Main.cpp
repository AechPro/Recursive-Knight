#include <vector>
#include <iostream>
#include <math.h>
#include <chrono>
using namespace std;
using namespace std::chrono;
int moveCounter = 0;
int* findNextPos(const int& moveFlag, const int& x, const int& y)
{
	int nextX = 0, nextY = 0;
	switch (moveFlag) //switch to set next position based on which move value is specified
	{
	case 1:
		nextX = x - 2;
		nextY = y - 1;
		break;
	case 2:
		nextX = x - 1;
		nextY = y - 2;
		break;
	case 3:
		nextX = x + 1;
		nextY = y - 2;
		break;
	case 4:
		nextX = x + 2;
		nextY = y - 1;
		break;
	case 5:
		nextX = x + 2;
		nextY = y + 1;
		break;
	case 6:
		nextX = x + 1;
		nextY = y + 1;
		break;
	case 7:
		nextX = x - 1;
		nextY = y + 2;
		break;
	case 8:
		nextX = x - 2;
		nextY = y + 1;
		break;
	}
	return new int[2]{ nextX, nextY };
}
void recursiveStep(int x, int y, int nextMove, bool pointList[8][8])
{
	if (nextMove > 8) { return; }
	int* tempMem = findNextPos(nextMove, x, y); // find next x and y values based on current move number, store in temporary array
    //tempMem[0] = x
	//tempMem[1] = y
	//check to make sure next x value is bounded by the chess board
	if (tempMem[0] >= 0 && tempMem[0] <= 7)
	{
		//check to make sure next y value is bounded by the chess board
		if (tempMem[1] >= 0 && tempMem[1] <= 7)
		{
			//check to see if next x and y values have not been traversed before
			if (!pointList[tempMem[0]][tempMem[1]])
			{
				cout << "MOVING TO " << tempMem[0] << "," << tempMem[1] << endl;
				//if next x and y values are the destination, return
				if (tempMem[0] == 0 && tempMem[1] == 2)
				{
					cout << "DESTINATION REACHED" << endl;
					return;
				}
				//update current x and y to next values
				x = tempMem[0];
				y = tempMem[1];
				//set bitmap flag at current x and y values
				pointList[x][y] = true;
				//recurse from here to iterate all possible branches of the initial branch set
				recursiveStep(x,y, nextMove, pointList);
				
			}
		}
	}
	delete[] tempMem; // delete temporary position array
	recursiveStep(x, y, nextMove + 1, pointList); // recurse into next branch set
}
void knightProblem()
{
	//create an 8x8 bitmap with false nodes
	bool pointList[8][8];
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			pointList[i][j] = false;
		}
	}
	//perform recursive function with starting point (0,2) and the first possible move for the knight to take
	recursiveStep(0, 2, 1, pointList);
}
int main()
{
	knightProblem();
	char a = 'i';
	cout << "press Q to quit..." << endl;
	while (a != 'q' && a != 'Q')
	{
		cin >> a;
	}
	return 0;
}
