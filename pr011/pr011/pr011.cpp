#include <iostream>

int main()
{
	setlocale(LC_ALL, "Russian");
	int a;
	int r = 1;
	std::cout << "Введите число" << std::endl;
	std::cin >> a;
	for (int i = 1; i < (a + 1); i++) {
		r = r * i;
	}
	std::cout << r << std::endl;
}