#include <iostream>


int main()
{
	int s, l1, r1, l2, r2, x1, x2;
	bool znach = false;
	std::cin >> s >> l1 >> r1 >> l2 >> r2;
	int sohzn = l2;// сохранил значение
	for (; l1 <= r1; l1++) { // перебирает первый диапазон
		for (l2 = sohzn; l2 <= r2; l2++) { // перебирает второй диапазон l2_2, чтобы возвращалось к началу, если не будет, то будет прибавляться последнее число
			if (l1 + l2 == s) {
				znach = true;
				break;
			}
		}
		if (znach) {
			break;
		}
	}
	x1 = l1;
	x2 = l2;
	if (znach) {
		std::cout << x1 << ' ' << x2 << std::endl;
	}
	else {
		std::cout << -1 << std::endl;
	}
}
