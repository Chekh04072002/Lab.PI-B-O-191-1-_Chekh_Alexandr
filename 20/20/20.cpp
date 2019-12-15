#include <iostream>

void sortirovka(int* arr, int size)
{
	for (int i = 0; i < size - 1; i++) // потому что массив нумеруется с ноля
	{
		int counter = 0;
		for (int j = 0; j < size - i - 1; j++)
			if (arr[j] > arr[j + 1])
			{
				int temp = arr[j]; // временная переменная
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				counter++;
			}
		if (!counter)break;
	}
}

void vivod(int* arr, int size)
{
	for (int i = 0; i < size; i++) {
		std::cout << arr[i] << ' ';
	}
}

int main()
{
	int n;
	std::cin >> n;
	int* array = new int[n];
	for (int i = 0; i < n; i++) {
		std::cin >> array[i];
	}
	sortirovka(array, n);
	vivod(array, n);
}