﻿#include <iostream>


int main()
{
	int s, l1, r1, l2, r2;
	bool znach = false;
	std::cin >> s >> l1 >> r1 >> l2 >> r2;
	int l2_2 = l2;// сохранил значение
	for (; l1 <= r1; l1++) { // перебирает первый диапазон
		for (l2 = l2_2; l2 <= r2; l2++) { // перебирает второй диапазон l2_2, чтобы возвращалось к началу, если не будет, то будет прибавляться последнее число
			if (l1 + l2 == s) {
				znach = true;
				break;
			}
		}
		if (znach) {
			break;
		}
	}
	if (znach) {
		std::cout << l1 << ' ' << l2 << std::endl;
	}
	else {
		std::cout << - 1 << std::endl;
	}
}