#include <iostream>
#include <ctime>
int main() {
	setlocale(LC_ALL, "russian");
	const int size = 20;
	srand(time(0));
	int max, min;
	max = -100;
	min = 100;
	int arr[size];
	for (int i = 0; i < size; i++) {
		arr[i] = -100 + rand() % 201; // сделал по формуле: r=min + rand() % (max-min+1)
	}
	for (int i = 0; i < size; i++){
		std::cout << arr[i] << " ";
		if (max < arr[i]) {
			max = arr[i];
		}
		if (min > arr[i]) {
			min = arr[i];
		}
	}
	std::cout << std::endl;
	std::cout << "Max= " << max << std::endl;
		std::cout << "Min= " << min << std::endl;
}