#include <iostream>
#include <ctime>

int main() {
	setlocale(LC_ALL, "Russian");
	srand(time(NULL) );
link:
	int namber, namber1, vib;
	std::cout << "Игра началась. Угадывайте число от 1 до 100" << std::endl;
	namber = rand() %
		100;
	for (int i = 0; i < 5; i++) {
		std::cin >> namber1;
		if (namber1 != namber) {
			if (namber1 > namber) {
				std::cout << "Загаданное число меньше" << std::endl;
			}
			else {
				std::cout << "Загаданное число больше" << std::endl;
			}
		}
		else {
			std::cout << "Поздравляю! Вы угадали!" << std::endl;
		}
	}
	std::cout << "Вы проиграли. Было загадано число:" << namber << std::endl;
	std::cout << "Хотите начать сначала? (1-Да)" << std::endl;
	std::cin >> vib;
	if (vib == 1) {
		goto link;
	}
	else {
		return 0;
	}
}