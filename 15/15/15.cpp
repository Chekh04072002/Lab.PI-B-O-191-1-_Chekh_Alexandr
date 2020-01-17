 #include <iostream>
int main() {
	setlocale(LC_ALL, "russian");
	int n, counter = 0, temp;
	std::cout << "Введите число элементов массива" << std::endl;
	std::cin >> n;
	int* mass = new int[n];
	std::cout << "Введите элементы массива" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cin >> mass[i];
		counter = counter + 1;
		for (int i = 0; i < counter - 1; i++) {
			for (int j = 0; j < counter - 1 - i; j++) {
				if (mass[j] > mass[j + 1]) {
					temp = mass[j];
					mass[j] = mass[j + 1];
					mass[j + 1] = temp;
				}
			}
		}

		if (counter < 5) {
			for (int perp = counter - 1; perp >= 0; perp--) {
				std::cout << mass[perp] << " ";
			}
		}
		else {
			for (int vtorp = 4; vtorp >= 0; vtorp--) {
				std::cout << mass[vtorp] << " ";
			}
		}
		std::cout << std::endl;
	}
	return 0;
	delete[] mass;
}