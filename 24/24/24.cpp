#include <iostream>

size_t mystrlen(const char* string)
{
	int dlin = 0;
	int i = 0;
	while (string[i] != '\0') // \0 означает конец строки
	{
		dlin++;
		i++;
	}
	return dlin;
}

int mystrcmp(const char* string1, const char* string2)
{
	int i = 0;
	while (string1[i] != '\0' && string2[i] != '\0')
	{
		i++;
		if (string1[i] > string2[i])return 1;
		if (string1[i] < string2[i])return -1;
	}
	return 0;
}

char* mystrstr(char* string1, const char* string2)
{
	for (int i = 0; i < mystrlen(string1); i++)
	{
		int i1 = 0;
		if (string1[i] == string2[i1])
		{
			int counter = 1;
			i1++;

			while ((string1[i + i1] == string2[i1]) && (i1 < mystrlen(string2))) {
				counter++;
				i1++;
			}
			if (counter == mystrlen(string2)) {
				return &string1[i];
			}
		}
	}
	return nullptr;
}

char* mystrcat(char* destptr, const char* srcptr)
{
	int len = mystrlen(destptr);
	for (int i = 0; i < mystrlen(srcptr); i++)
		destptr[len + i] = srcptr[i];
	destptr[len + mystrlen(srcptr)] = '\0';
	return destptr;
}

int main()
{
	setlocale(LC_ALL, "Russian");
	char stroka1[101];
	char stroka2[51];
	std::cin.getline(stroka1, 101);
	std::cin.getline(stroka2, 51);

	std::cout << mystrlen(stroka1) << " ";
	std::cout << mystrlen(stroka2) << std::endl;

	if (mystrcmp(stroka1, stroka2) == 1) std::cout << "Строка 1 больше строки 2" << std::endl;
	else if (mystrcmp(stroka1, stroka2) == -1) std::cout << "Строка 2 больше строки 1" << std::endl;
	else std::cout << "Строки равны" << std::endl;

	int i = 0;
	if (mystrstr(stroka1, stroka2)) while (&stroka1[i] != mystrstr(stroka1, stroka2)) i++;
	else i = -1;
	std::cout << i << std::endl;

	std::cout << mystrcat(stroka1, stroka2);
}
