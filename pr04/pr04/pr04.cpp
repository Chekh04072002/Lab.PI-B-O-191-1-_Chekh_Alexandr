#include <iostream>
int main()
{
	double a, b;
	std::cout << "Enter a and b: ";
	std::cin >> a >> b;
	std::cout << "a=" << a << "; b=" << b << std::endl;
	double q;
	q = a;
	a = b;
	b = q;
	std::cout << "a=" << a << "; b=" << b << std::endl;
	b = b + a;
	a = b - a;
	b = b - a;
	std::cout << "a=" << a << "; b=" << b << std::endl;
}
