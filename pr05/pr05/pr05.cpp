#include <iostream>

int main()
{
	setlocale(LC_ALL, "russian");
	double x, x0, v0, t, a = -9.8;
	std::cout << "Введите x0, v0, t " << std::endl;
	std::cin >> x0 >> v0 >> t;
	x = x0 + v0 * t + a * t * t / 2;
	std::cout << x << std::endl;
}
