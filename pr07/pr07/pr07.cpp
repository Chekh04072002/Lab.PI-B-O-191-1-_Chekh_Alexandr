#include <iostream>
#include <math.h>

int main()
{
	setlocale(LC_ALL, "russian");
	int x;
	double a, b, c, a1, b1, c1, a2, b2, c2, p, S;
		std::cout << "Выберите способ ввода параметров 1 (через длины сторон) или 2 (через координаты)" << std::endl;
		std::cin >> x;
	if (x == 1) {
		std::cout << "Введите длины сторон" << std::endl;
		std::cin >> a;
		std::cin >> b;
		std::cin >> c;
		if (a + b <= c || b + c <= a || a + c <= b) {
			std::cout << "Сумма двух сторон не может быть меньше или равна третей" << std::endl;
		}
		else {
			p = (a + b + c) / 2.0;
			S = sqrt(p * (p - a) * (p - b) * (p - c));
			std::cout << "S = " << S << std::endl;
		}
	}
	else {
		std::cout << "Введите координаты вершин" << std::endl;
		std::cin >> a1 >> a2;
		std::cin >> b1 >> b2;
		std::cin >> c1 >> c2;
		if ((a1 == b1 && a2 == b2) || (b1 == c1 && b2 == c2) || (a1 == c1 && a2 == c2) || (a1 == b1 && a1 == c1) || (a2 == b2 && b2 == c2)) {
			std::cout << "Это не треугольник";
		}
		else {
			a = sqrt(pow(a2 - a1, 2) + pow(b2 - b1, 2));
			b = sqrt(pow(b2 - b1, 2) + pow(c2 - c1, 2));
			c = sqrt(pow(c2 - c1, 2) + pow(a2 - a1, 2));
			if (a + b <= c || b + c <= a || a + c <= b) {
				std::cout << "Сумма двух сторон не может быть меньше или равна третей" << std::endl;
			}
			else {
				p = (a + b + c) / 2.0;
				S = sqrt(p * (p - a) * (p - b) * (p - c));
				std::cout << "S = " << S << std::endl;
			}
		}
	}
}
