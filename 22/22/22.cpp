#include <iostream>
void swap(int* a, int* b) { 
	int vr = *a;
	*a = *b; // значение по адресу
	*b = vr;
}

int msort(int* a, int* b, int* c)
{
	if (*a > *b)swap(b, a); // b самая большая
	if (*b > *c)swap(c, b); // самая большая - c
	if (*c > *a)swap(a, c); // а самая большая
	return *a;
}
void info(const int* a) {
	std::cout << "Адресс:" << " " <<  a << ";" << " " << "Значение" << " " << *a << ";" << std::endl;
}
int* add(int* a, const int* b)
{
	int sum = *a + *b;
	*a = sum;
	return a;
}
int main() {
	setlocale(LC_ALL, "Russian");
	int num1 = 3, num2 = 4, num3 = 5;
	info(&num1); 
	info(&num2);
	info(&num3);
	std::cout << "Максимум: " << msort(&num1, &num2, &num3) << std::endl;
	 add(&num1, add(&num2, &num3)); //  вычисляет сумму значений по указанным адресам и сохраняет результат по первому адресу, этот же адрес возвращается в качестве результата
	info(&num1);

}