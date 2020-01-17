#include <iostream>
#include <math.h>


int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b, c, D, x1, x2;
	std::cout << "Введите a" << std::endl;
	std::cin >> a;
	std::cout << "Введите b" << std::endl;
	std::cin >> b;
	std::cout << "Введите c" << std::endl;
	std::cin >> c;
	if (a == 0 && b == 0) {
		std::cout << "x - любое число" << std::endl;
	}
	else if (a == 0 && c == 0 || b == 0 && c == 0) {
		x1 = 0;
		std::cout << "x = " << x1 << std::endl;
	}
	else if (a == 0) {
		x1 = -c / b;
		std::cout << "x = " << x1 << std::endl;
	}
	else if (b == 0) {
		if (-c < 0) {
			std::cout << "Нет действительных корней уравнения" << std::endl;
		}
		else {
			x1 = sqrt(-c / a);
			x2 = -sqrt(-c / a);
			std::cout << "x1 = " << x1 << std::endl << "x2 = " << x2 << std::endl;
		}
	}
	else if (c == 0) {
		x1 = 0;
		x2 = -b / a;
		std::cout << "x1 = " << x1 << std::endl << "x2 = " << x2 << std::endl;
	}
	else {
		D = b * b - 4 * a * c;
		if (D < 0) {
			std::cout << "Нет действительных корней уравнения" << std::endl;
		}
		else if (D == 0) {
			std::cout << "x = " << -b / (2 * a) << std::endl;
		}
		else {
			std::cout << "x1 = " << (-b + sqrt(D)) / (2 * a) << std::endl;
			std::cout << "x2 = " << (-b - sqrt(D)) / (2 * a) << std::endl;
		}
	}
}
