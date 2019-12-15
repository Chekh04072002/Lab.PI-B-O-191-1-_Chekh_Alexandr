#include <iostream>
int main() {
	setlocale(LC_ALL, "russian");
	const int str = 10;
	const int stlb = 8;
	int arr[str][stlb] = { 0 };
	/*for (int i = 0; i < str; i++) {
		for (int j = 0; j < stlb; j++) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	*/
	arr[rand() % 10][rand() % 8] = 5;
	int stroku, stolb;
	

	for (int i = 0; i < str; i++) {
		for (int j = 0; j < stlb; j++) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	int counter = 0;
	while (counter < 5) {
		std::cout << "Введите номер строки и номер столбца" << std::endl;
		std::cin >> stroku >> stolb;
		stroku = stroku - 1;
		stolb = stolb - 1;

		if (stroku > 10 || stroku < 0 || stolb < 0 || stolb > 8) {
			std::cout << "Выход за границу массива" << std::endl;
			continue;
		}
		if (arr[stroku][stolb] == 5) {
			std::cout << "Вы угадали" << std::endl;
			return 0;
		}
		else if (arr[stroku][stolb] != 5) {
			std::cout << "Вы не угадали" << std::endl;
			arr[stroku][stolb] = 1;
			counter++;
		}
		else if (arr[stroku][stolb] == 1) {
			std::cout << "Эта ячейка была ранне проверена вами" << std::endl;
		}

	}
	std::cout << "Вы проиграли" << std::endl;
}