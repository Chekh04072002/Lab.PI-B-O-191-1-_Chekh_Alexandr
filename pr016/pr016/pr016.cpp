#include <iostream>
#include <vector>

void factorization(int n) {
	std::vector<int> mnoz;
	int counter = 0;
	int pow = 1;
	while (n != 1) {
		for (int i = 2; i <= n; i++) {
			if (!(n % i)) {
				n /= i;
				mnoz.push_back(i);
				counter++;
				break;
			}
		}
	}
	for (auto it = mnoz.begin(); it != mnoz.end(); it++) {
		if (it != mnoz.end() - 1 && *it == *(it + 1)) { // С начала по конец вектора ищет одинаковые числа, чтобы потом выразить степень
			pow++;
		}
		else if (pow > 1) {
			std::cout << *it << "^" << pow; // Выводит число со степенью, если степень больше 1
			pow = 1;
		}
		else std::cout << *it; // Выводит просто число, если оно без степени
		if ((it != mnoz.end() - 1) && (pow <= 1)) {
			std::cout << "*";
		}
	}
}
int main()
{

	int a;
	std::cin >> a;
	factorization(a);
}