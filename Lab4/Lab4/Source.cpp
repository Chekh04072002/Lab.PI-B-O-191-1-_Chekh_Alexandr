#include "Header.h"
#include <iostream>

Game initGame(char Userchar) {
	Game starting;
	for (int i = 0; i < 3; i++)
		for (int k = 0; k < 3; k++) {
			starting.board[i][k] = ' ';
		}
	starting.isUserTurn = rand() % 2;
	starting.userChar = Userchar;
	if (Userchar == 'X') {
		starting.botChar = '0';
	}
	else {
		starting.botChar = 'X';
	}
	starting.status = PLAY;
	updateDisplay(starting);
	return starting;
}

void updateDisplay(const Game game) {
	system("CLS");
	std::cout << "    1   2   3\n  -------------\n";
	for (int i = 0; i < 3; i++) {
		std::cout << i + 1 << " | ";
		for (int k = 0; k < 3; k++) {
			std::cout << game.board[i][k] << " | ";
		}
		std::cout << "\n  -------------\n";
	}
}

void botTurn(Game* game) {
	int Counter = 0;
	for (int i = 0; i < 3; i++) {
		for (int k = 0; k < 3; k++) {
			if (game->board[i][k] != ' ') {
				Counter++;
			}
		}
	}
	if (!Counter) {
		game->board[1][1] = game->botChar;
		return;
	}
	Counter = 0;
	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == game->userChar) {
			Counter++;
		}
		else if (game->board[i][i] == game->botChar) {
			Counter--;
		}
	}
	if (Counter == 2) {
		for (int l = 0; l < 3; l++) {
			if (game->board[l][l] == ' ') {
				game->board[l][l] = game->botChar;
				return;
			}
		}
	}
	Counter = 0;
	for (int i = 0; i < 3; i++) {
		if (game->board[i][2 - i] == game->userChar) {
			Counter++;
		}
		else if (game->board[i][2 - i] == game->botChar) {
			Counter--;
		}
	}
	if (Counter == 2) {
		for (int l = 0; l < 3; l++) {
			if (game->board[l][2 - l] == ' ') {
				game->board[l][2 - l] = game->botChar;
				return;
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		Counter = 0;
		for (int k = 0; k < 3; k++) {
			if (game->board[i][k] == game->userChar) {
				Counter++;
			}
			else if (game->board[i][k] == game->botChar) {
				Counter--;
			}
		}
		if (Counter == 2) {
			for (int l = 0; l < 3; l++) {
				if (game->board[i][l] == ' ') {
					game->board[i][l] = game->botChar;
					return;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		Counter = 0;
		for (int k = 0; k < 3; k++) {
			if (game->board[k][i] == game->userChar) {
				Counter++;
			}
			else if (game->board[k][i] == game->botChar) {
				Counter--;
			}
		}
		if (Counter == 2) {
			for (int l = 0; l < 3; l++) {
				if (game->board[l][i] == ' ') {
					game->board[l][i] = game->botChar;
					return;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		Counter = 0;
		for (int k = 0; k < 3; k++) {
			if (game->board[i][k] == game->userChar) {
				Counter++;
			}
			else if (game->board[i][k] == game->botChar) {
				Counter--;
			}
		}
		if (Counter == 1) {
			for (int l = 0; l < 3; l++) {
				if (game->board[i][l] == ' ') {
					game->board[i][l] = game->botChar;
					return;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++) {
		Counter = 0;
		for (int k = 0; k < 3; k++) {
			if (game->board[k][i] == game->userChar) {
				Counter++;
			}
			else if (game->board[k][i] == game->botChar) {
				Counter--;
			}
		}
		if (Counter == 1) {
			for (int l = 0; l < 3; l++) {
				if (game->board[l][i] == ' ') {
					game->board[l][i] = game->botChar;
					return;
				}
			}
		}
	}
	for (int i = 0; i < 3; i++)
		for (int k = 0; k < 3; k++)
			if (game->board[i][k] == ' ') {
				game->board[i][k] = game->botChar;
				return;
			}
}

void userTurn(Game* game) {
	int a, b;
	std::cout << "Ваш ход: ";
	std::cin >> a >> b;
	while (a < 1 || a > 3 || b < 1 || b > 3 || game->board[a - 1][b - 1] != ' ') {
		std::cout << "Неверные координаты" << std::endl;
		std::cout << "Ваш ход: ";
		std::cin >> a >> b;
	}
	game->board[a - 1][b - 1] = game->userChar;
}

void Winn(Game* game, int a) {
	if (a == 3) {
		game->status = USER_WIN;
	}
	else if (a == -3) {
		game->status = BOT_WIN;
	}
}

bool updateGame(Game* game) {
	int counter;
	for (int i = 0; i < 3; i++) {
		counter = 0;
		for (int k = 0; k < 3; k++) {
			if (game->board[i][k] == game->userChar) {
				counter++;
			}
			else if (game->board[i][k] == game->botChar) {
				counter--;
			}
		}
		Winn(game, counter);
	}
	for (int i = 0; i < 3; i++) {
		counter = 0;
		for (int k = 0; k < 3; k++) {
			if (game->board[k][i] == game->userChar) {
				counter++;
			}
			else if (game->board[k][i] == game->botChar) {
				counter--;
			}
		}
		Winn(game, counter);
	}
	counter = 0;
	for (int i = 0; i < 3; i++) {
		if (game->board[i][i] == game->userChar) {
			counter++;
		}
		else if (game->board[i][i] == game->botChar) {
			counter--;
		}
	}
	Winn(game, counter);
	counter = 0;
	for (int i = 0; i < 3; i++) {
		if (game->board[i][2 - i] == game->userChar) {
			counter++;
		}
		else if (game->board[i][2 - i] == game->botChar) {
			counter--;
		}
	}
	Winn(game, counter);
	if (game->status == PLAY) {
		counter = 0;
		for (int i = 0; i < 3; i++) {
			for (int k = 0; k < 3; k++) {
				if (game->board[i][k] == ' ') {
					counter++;
				}
			}
		}
		if (!counter) {
			game->status = NOT_WIN;
			return true;
		}
		game->isUserTurn = !game->isUserTurn;
		return false;
	}
	return true;
}