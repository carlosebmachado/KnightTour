#include <iostream>
#include <iomanip>

#include "watch.h"

void printLine(int n = 1)
{
	for (size_t i = 0; i < n; i++)
	{
		std::cout << std::endl;
	}
}

void printBoard(int** board, int N)
{
	for (size_t i = 0; i < N; i++)
	{
		for (size_t j = 0; j < N; j++)
		{
			std::cout << " " << std::setw(2) << board[i][j];
		}
		printLine();
	}
}

int knightTour(int i, int x, int y, int** board, int N, int xMove[], int yMove[], int &steps)
{
	steps++;
	if (i == N * N)
	{
		return 1;
	}
	for (int k = 0; k < 8; k++)
	{
		int newX = x + xMove[k];
		int newY = y + yMove[k];

		if (newX >= 0 && newX < N && newY >= 0 && newY < N && board[newY][newX] == -1)
		{
			board[newY][newX] = i;
			if (knightTour(i + 1, newX, newY, board, N, xMove, yMove, steps))
			{
				return 1;
			}
			else
			{
				board[newY][newX] = -1;
			}
		}
	}
	return 0;
}

int pathOptions(int x, int y, int** board, int N, int xMove[], int yMove[]) {
	int options = 0;
	for (int k = 0; k < 8; k++)
	{
		int newX_Temp = x + xMove[k];
		int newY_Temp = y + yMove[k];

		if (newX_Temp >= 0 && newX_Temp < N && newY_Temp >= 0 && newY_Temp < N && board[newY_Temp][newX_Temp] == -1)
		{
			options++;
		}
	}
	return options;
}

int knightTourHeuristc(int i, int x, int y, int** board, int N, int xMove[], int yMove[], int& steps)
{
	steps++;
	if (i == N * N)
	{
		return 1;
	}

	int options = 0;
	int min_options = 10;
	int k_def = -1;

	for (int k = 0; k < 8; k++)
	{
		int newX_Temp = x + xMove[k];
		int newY_Temp = y + yMove[k];

		if (newX_Temp >= 0 && newX_Temp < N && newY_Temp >= 0 && newY_Temp < N && board[newY_Temp][newX_Temp] == -1)
		{
			options = pathOptions(newX_Temp, newY_Temp, board, N, xMove, yMove);
		}

		if (options < min_options && options != 0)
		{
			min_options = options;
			k_def = k;
		}
		else if (options == 0) {
			if (newX_Temp >= 0 && newX_Temp < N && newY_Temp >= 0 && newY_Temp < N && board[newY_Temp][newX_Temp] == -1 && k_def == -1)
			{
				k_def = k;
			}
		}
	}

	if (k_def != -1)
	{
		int newX = x + xMove[k_def];
		int newY = y + yMove[k_def];

		if (newX >= 0 && newX < N && newY >= 0 && newY < N && board[newY][newX] == -1)
		{
			board[newY][newX] = i;
			if (knightTourHeuristc(i + 1, newX, newY, board, N, xMove, yMove, steps))
			{			
				return 1;
			}
			else
			{
				board[newY][newX] = -1;
			}
		}
	}

	return 0;
}

int menu() {
	int option = -1;
	std::cout << "Choose some option:" << std::endl;
	std::cout << "1 - Solve board without heuristics" << std::endl;
	std::cout << "2 - Solve board with heuristics" << std::endl;
	std::cout << "3 - Exit" << std::endl;
	std::cout << "Option: ";
	std::cin >> option;

	system("cls");
	return option;
}

int main()
{
	ChronoStopwatch csw;
	int steps = 0;
	int result = 0;
	int** board = new int* [1];
	int xMove[] = { 2, 1, -1, -2, -2, -1,  1,  2 };
	int yMove[] = { 1, 2,  2,  1, -1, -2, -2, -1 };
	int N = 0;
	int x = 0, y = 0;
	bool exit = false;

	do {
		int option = menu();
		steps = 0;

		if (!(option >= 1 && option <= 2))
			return 0;

		if (option == 1 || option == 2)
		{
			std::cout << "Board size: ";
			std::cin >> N;
			std::cout << "Start X: ";
			std::cin >> x;
			std::cout << "Start Y: ";
			std::cin >> y;
			printLine();

			board = new int* [N];
			for (size_t i = 0; i < N; i++)
			{
				board[i] = new int[N];
				for (size_t j = 0; j < N; j++)
				{
					board[i][j] = -1;
				}
			}
			board[y][x] = 0;

			//printBoard(board);
			//system("PAUSE");
		}

		if (option == 1)
		{
			csw.start();
			result = knightTour(1, x, y, board, N, xMove, yMove, steps);
			csw.stop();
		}
		else if (option == 2) {
			csw.start();
			result = knightTourHeuristc(1, x, y, board, N, xMove, yMove, steps);
			csw.stop();
		}


		if (!result)
		{
			std::cout << "Solution does not exist" << std::endl;
		}
		else
		{
			std::cout << "Elapsed: " << csw.getElapsedFormated() << std::endl;
			std::cout << "Steps: " << steps << std::endl;
			std::cout << "Board: " << std::endl;
			printBoard(board, N);
		}
		steps = 0;
		std::cout << std::endl;
	} while (!exit);

	return 0;
}
