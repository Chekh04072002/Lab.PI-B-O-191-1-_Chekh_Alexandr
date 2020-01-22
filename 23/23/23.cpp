#include <iostream>

bool Chislo(int i)
{
	if (i >= 48 && i <= 57)return true;
	return false;
}

bool Bukva(int i)
{
	if ((i >= 65 && i <= 90) || (i >= 97 && i <= 122))return true;
	return false;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char first[21], bez_pro[21] = { 0 };
	std::cin.getline(first, 21);

	for (int i = 0, n = 0; i < strlen(first); i++) // Проверяются на подходящие символы и заносятся во второй вектор без пробелов
		if (Chislo((int)first[i]) || Bukva((int)first[i])) {
			bez_pro[n] = first[i];
			n++;
		}

	bool ne_pal = true;
	int length = strlen(bez_pro); // Длина
	if (length) {
		for (int l = 0; l < length / 2; l++) { // середина - граница, -1 и -l, так как проверяется на палиндром соответствующие элементы от начала и с конца
			if (Chislo((int)bez_pro[l]) && bez_pro[l] != bez_pro[length - 1 - l]) {
				ne_pal = false;
				break;
			}

			else if ((int)bez_pro[l] != (int)bez_pro[length - 1 - l] && (int)bez_pro[l] + 32 != (int)bez_pro[length - 1 - l] && (int)bez_pro[l] - 32 != (int)bez_pro[length - 1 - l]) { // +32 и -32, так как проверяются буквы в разном реестре и все они подходят
				ne_pal = false;
				break;
			}
		}
	}
	else ne_pal = false;
	if (ne_pal) std::cout << "Палиндром";
	else std::cout << "Не палиндром";
}
