#include <iostream>
int main() {
	setlocale(LC_ALL, "russian");
	long long  n, p = 1, sum = 1;
	std::cout << "Введите число" << std::endl;
	std::cin >> n;
	if (n == 0) {
		std::cout << 0 << std::endl;
	}
	else
	{
		while ((p *= 2) <= n)
			sum++;
		std::cout << sum << std::endl;
	}
	return 0;

}