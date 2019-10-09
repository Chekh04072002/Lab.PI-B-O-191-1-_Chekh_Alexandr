#include <iostream>
int main() {
	setlocale(LC_ALL, "Russian");
	double A = 0;
	int k = 0;
	double r = 1;
	std::cout << "Введите число " << std::endl;
	std::cin >> A;
	std::cout << "Введите целую степень " << std::endl;
	std::cin >> k;
	for (int i = 0; i < k; i++) {
		r = r * A;
	}
	std::cout << "Ответ:" << " " << r << std::endl;

	return 0;
}