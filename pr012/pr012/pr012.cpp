#include <iostream>

int main() {
	setlocale(LC_ALL, "russian");

	int a, b;
	std::cout << "Введите число" << std::endl;
	std::cin >> a;
	for (int i = a - 1; i > 1; i--) {
		if (a % i == 0) {
			std::cout << "Число составное" << std::endl;

			return 0;
		}

	}
	std::cout << "Число простое" << std::endl;
	return 0;

}