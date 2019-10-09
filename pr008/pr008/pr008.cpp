#include <iostream>
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double a, b;
	char c;
	cout << "Введите первое вещественное число" << endl;
	cin >> a;
	cout << "Введите символ-знак операции" << endl;
	cin >> c;
	cout << "Введите второе вещественное число" << endl;
	cin >> b;
	if (c == '+') {
		cout << a + b << endl;
	}
	else if (c == '*') {
		cout << a * b << endl;
	}
	else if (c == '/') {
		cout << a / b << endl;
	}
	else cout << "Неправильный ввод" << endl;
	return 0;
}