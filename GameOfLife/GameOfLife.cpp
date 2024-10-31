#include <iostream>
#include <string>
#include <time.h>
#include <Windows.h>
using namespace std;
const int rows = 20;
const int cols = 20;
void make2DArray(int arr[][cols]);
void printArray(int arr[][cols]);
int neighborsCount(int arr[][cols], int x, int y);
void swap(int arr[][cols], int next[][cols]);
bool checkerEqualArray(int arr[][cols], int next[][cols]);

int main()
{
	int counter = 0;
	srand(time(0));
	int arr[rows][cols]{}, next[rows][cols]{}, reserve[rows][cols]{};
	make2DArray(arr);
	printArray(arr);
	bool flag = true;
	while (flag)
	{
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				int state = arr[i][j];
				// Count live neighbors
				int sum = 0;
				int neighbors = neighborsCount(arr, i, j);
				if (state == 0 && neighbors == 3)
				{
					next[i][j] = 1;
				}
				else if (state == 1 && (neighbors < 2 || neighbors > 3))
				{
					next[i][j] = 0;
				}
				else
				{
					next[i][j] = state;
				}
			}
		}
		if (checkerEqualArray(arr, next))
		{
			flag = false;
		}
		swap(arr, next);
		if (counter == 2)
		{
			if (checkerEqualArray(reserve, arr))
			{
				flag = false;
			}
			else
			{
				swap(reserve, arr);
			}
			counter = 0;
		}
		Sleep(100);
		system("cls");
		if (flag) 
		{
			printArray(next);
		}
		else
		{
			cout << "GameOver!" << endl;
			printArray(next);
		}
		counter++;
	}
	return 0;
}

void make2DArray(int arr[][cols])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = rand() % 2;
		}
	}
}
void printArray(int arr[][cols])
{
	cout << "----------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (arr[i][j] == 1)
			{
				cout << "*|";
			}
			else
			{
				cout << " |";
			}
		}
		cout << endl;
	}
	cout << "----------------------------------------------------------------------------------------------------" << endl;
}
int neighborsCount(int arr[][cols], int x, int y)
{
	int sum = 0;
	for (int i = -1; i < 2; i++)
	{
		for (int j = -1; j < 2; j++)
		{
			int row = (x + i + rows) % rows;
			int col = (y + j + cols) % cols;
			sum += arr[row][col];
		}
	}
	sum -= arr[x][y];
	return sum;
}
// Update Array
void swap(int arr[][cols], int next[][cols])
{
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = next[i][j];
		}
	}
}

// Check for EndGame
bool checkerEqualArray(int arr[][cols], int next[][cols])
{
	bool flag = true;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (arr[i][j] != next[i][j])
			{
				flag = false;
				break;
			}
		}
		if (!flag)
		{
			break;
		}
	}
	return flag;
}